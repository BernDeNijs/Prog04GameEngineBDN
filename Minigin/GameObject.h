#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace dae
{
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
		glm::vec3 GetLocalPosition();
		glm::vec3 GetWorldPosition();

		void SetLocalPosition(glm::vec3 position);
		void SetLocalPosition(glm::vec2 position);

		//SCENEGRAPH
		std::weak_ptr<GameObject> GetParent() { return m_pParent; }
		void SetParent(const std::shared_ptr<GameObject>& parent, bool keepWorldPosition);



	private:
		std::unordered_map<std::type_index, std::shared_ptr<GameComponent>> m_pComponents;
		bool m_MarkedForDeath{ false };

		//SCENEGRAPH
		std::weak_ptr<GameObject> m_pParent{ std::weak_ptr<GameObject>()};
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};
		bool IsChild(std::shared_ptr<dae::GameObject> potentialChild) const;

		//POSITION
		bool m_PositionDirty = false;
		glm::vec3 m_LocalPosition { 0,0,0 };
		glm::vec3 m_WorldPosition { 0,0,0 };
		//glm::vec3 m_LocalRotation { 0,0,0 };
		//glm::vec3 m_WorldRotation { 0,0,0 };
		//glm::vec3 m_LocalScale { 0,0,0 };
		//glm::vec3 m_WorldScale { 0,0,0 };

		void SetPositionDirty();
		void UpdateWorldPosition();
	};


}
