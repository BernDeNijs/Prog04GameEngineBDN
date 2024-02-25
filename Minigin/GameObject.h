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
		T* GetComponent()
		{
			if (const auto found = m_pComponents.find(typeid(T));
				found != m_pComponents.end()) {
				return static_cast<T*>(found->second.get());
			}

			return nullptr;

		}

		template <typename T> bool HasComponent()const
		{
			const auto it = m_pComponents.find(typeid(T));
			return (it != m_pComponents.end());
		}


		//POSITION
		std::shared_ptr<TransformComponent> GetTransform() { return m_pTransform; }
		void SetTransform(glm::vec2 position) const;

		void SetTransform(glm::vec3 position) const;

	private:
		std::unordered_map<std::type_index, std::shared_ptr<GameComponent>> m_pComponents;
		std::shared_ptr<TransformComponent> m_pTransform;
	};


}
