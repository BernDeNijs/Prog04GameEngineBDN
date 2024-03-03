#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
//#include "GameTime.h"


namespace dae
{
	struct Transform
	{
		glm::vec3 Position = { 0,0,0 };
		glm::vec3 Rotation = { 0,0,0 };
		glm::vec3 Scale = { 0,0,0 };

		Transform operator+(const Transform& other) const {
			Transform result;
			result.Position = Position + other.Position;
			result.Rotation = Rotation + other.Rotation;
			result.Scale = Scale * other.Scale;
			return result;
		}
		Transform operator-(const Transform& other) const {
			Transform result;
			result.Position = Position - other.Position;
			result.Rotation = Rotation - other.Rotation;
			result.Scale = Scale / other.Scale;
			return result;
		}
	};
	struct ObjectTransform
	{
		Transform LocalTransform = Transform();
		Transform WorldTransform = Transform();
		bool IsDirty = false;
	};

	class GameComponent;
	class GameObject final 
	{
	public:
		void Update();
		void LateUpdate();
		void FixedUpdate();
		void Render() const;

		GameObject();
		GameObject(const std::shared_ptr<GameObject>& parent, bool keepWorldPosition);

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;



		//COMPONENT FUNCTIONS
		template<typename T, typename... Args>
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<GameComponent, T>::value, "Cannot add component that does not inherit from GameComponent");
			auto component = std::make_shared<T>(this, args...);
			m_pComponents.emplace(typeid(T),component);
			return component;
		}

		template<typename T>
		void RemoveComponent()
		{
			m_pComponents.erase(typeid(T));
		}

		template<typename T>
		std::weak_ptr<T> GetComponent()
		{
			if (const auto found = m_pComponents.find(typeid(T));
				found != m_pComponents.end()) {
				return std::static_pointer_cast<T>(found->second);
			}
			return std::weak_ptr<T>();
		}

		template <typename T> bool HasComponent()const
		{
			const auto it = m_pComponents.find(typeid(T));
			return (it != m_pComponents.end());
		}

		//DEATH
		bool GetDeathFlag() const { return m_MarkedForDeath; }
		void SetDeathFlag() { m_MarkedForDeath = true; }


		//POSITION
		dae::Transform GetLocalTransform() const;
		dae::Transform GetWorldTransform();

		void SetLocalTransform(const Transform& transform);
		void SetLocalPosition(glm::vec3 position);
		void SetLocalPosition(glm::vec2 position);
		
		void SetLocalRotation(glm::vec3 rotation);

		void SetLocalScale(glm::vec3 scale);
		void SetLocalScale(float scale);

	

		//SCENEGRAPH
		std::weak_ptr<GameObject> GetParent() { return m_pParent; }
		void SetParent(const std::shared_ptr<GameObject>& parent, bool keepWorldPosition);



	private:
		std::unordered_map<std::type_index, std::shared_ptr<GameComponent>> m_pComponents;
		bool m_MarkedForDeath{ false };

		//SCENEGRAPH
		std::weak_ptr<GameObject> m_pParent{ std::weak_ptr<GameObject>()};
		std::vector<GameObject*> m_pChildren{};
		bool IsChild(const std::shared_ptr<dae::GameObject>& potentialChild) const;

		//POSITION
		//bool m_PositionDirty = false;
		ObjectTransform m_Transform = ObjectTransform();

		//glm::vec3 m_LocalPosition { 0,0,0 };
		//glm::vec3 m_WorldPosition { 0,0,0 };
		//glm::vec3 m_LocalRotation { 0,0,0 };
		//glm::vec3 m_WorldRotation { 0,0,0 };
		//glm::vec3 m_LocalScale { 0,0,0 };
		//glm::vec3 m_WorldScale { 0,0,0 };

		void SetTransformDirty();
		void UpdateWorldTransform();
	};


}
