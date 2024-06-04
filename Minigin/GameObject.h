#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "GameComponent.h"
#include "Scene.h"

namespace bdnE
{
	struct Transform
	{
		glm::vec2 Position = { 0,0};
		float Rotation = 0;
		glm::vec2 Scale = { 1,1 };

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

	class GameObject final 
	{
	private:
		GameObject() = default;
		GameObject(GameObject* parent, bool keepWorldPosition);

		friend GameObject* Scene::CreateGameObject();
		friend GameObject* Scene::CreateGameObject(GameObject* parent, bool keepWorldPosition);
		
	public:

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//UPDATES
		void Update();
		void LateUpdate();
		void FixedUpdate();
		void Render() const;
		void RenderImgui() const;

		//COMPONENT FUNCTIONS
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of_v<GameComponent, T>, "Cannot add component that does not inherit from GameComponent");
			std::unique_ptr<T> component = std::make_unique<T>(this, args...);
			T* ptr = component.get();
			m_pComponents.emplace(typeid(T),std::move(component));
			return ptr;
		}

		template<typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of_v<GameComponent, T>, "Cannot remove component that does not inherit from GameComponent");
			m_pComponents.erase(typeid(T));
		}

		template<typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of_v<GameComponent, T>, "Cannot get component that does not inherit from GameComponent");
			if (const auto& found = m_pComponents.find(typeid(T));
				found != m_pComponents.end())
			{
				std::unique_ptr<GameComponent>& ptr = m_pComponents.at(typeid(T));
				GameComponent* rawPtr = ptr.get();
				return static_cast<T*>(rawPtr);
			}
			return nullptr;
		}
		

		template <typename T> 
		bool HasComponent()const
		{
			static_assert(std::is_base_of_v<GameComponent, T>, "Cannot get component that does not inherit from GameComponent");
			const auto it = m_pComponents.find(typeid(T));
			return (it != m_pComponents.end());
		}

		//DEATH
		bool GetDeathFlag() const { return m_MarkedForDeath; }
		void SetDeathFlag() { m_MarkedForDeath = true; }


		//TRANSFORM
		bdnE::Transform GetLocalTransform() const;
		bdnE::Transform GetWorldTransform();

		void SetLocalTransform(const Transform& transform);

		void SetLocalPosition(glm::vec2 position);
		
		void SetLocalRotation(float rotation);

		void SetLocalScale(glm::vec2 scale);
		void SetLocalScale(float scale);

		//SCENEGRAPH
		GameObject* GetParent() const { return m_pParent; }
		void SetParent(bdnE::GameObject* parent, bool keepWorldPosition);
		std::vector<GameObject*> GetChildren() { return m_pChildren; }

	private:
		//COMPONENTS
		std::unordered_map<std::type_index, std::unique_ptr<GameComponent>> m_pComponents;
		
		bool m_MarkedForDeath{ false };

		//SCENEGRAPH
		GameObject* m_pParent{ nullptr};
		std::vector<GameObject*> m_pChildren{};
		bool IsChild(bdnE::GameObject* potentialChild) const;

		//TRANSFORM
		struct ObjectTransform
		{
			Transform LocalTransform = Transform();
			Transform WorldTransform = Transform();
			bool IsDirty = false;
		};
		ObjectTransform m_Transform = ObjectTransform();
		void SetTransformDirty();
		void UpdateWorldTransform();
	};


}
