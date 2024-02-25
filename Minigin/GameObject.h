#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace dae
{
	class GameComponent;
	class TransformComponent;
	class GameObject final 
	{
	public:
		virtual void Update();
		virtual void LateUpdate();
		virtual void FixedUpdate();
		virtual void Render() const;

		GameObject();
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


		//POSITION
		std::weak_ptr<TransformComponent> GetTransform() { return m_pTransform; }
		void SetTransform(glm::vec2 position) const;

		void SetTransform(glm::vec3 position) const;

		bool GetDeathFlag() const { return m_MarkedForDeath; }
		void SetDeathFlag() { m_MarkedForDeath = true; }

	private:
		std::unordered_map<std::type_index, std::shared_ptr<GameComponent>> m_pComponents;
		std::shared_ptr<TransformComponent> m_pTransform;
		bool m_MarkedForDeath{ false };
	};


}
