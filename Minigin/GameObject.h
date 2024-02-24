#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Transform.h"

namespace dae
{
	class GameComponent;

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
		T* AddComponent(Args&&... args) {
			auto component = std::make_unique<T>(std::forward<Args>(args)...);
			T* ptr = component.get();
			m_pComponents.emplace(typeid(T), std::move(component));
			m_pComponents[typeid(T)]->SetOwner(this);
			return ptr;
		}

		template<typename T>
		void RemoveComponent() {
			m_pComponents.erase(typeid(T));
		}

		template<typename T>
		T* GetComponent() {			
			if (const auto found = m_pComponents.find(typeid(T)); 
				found != m_pComponents.end()) {
				return static_cast<T*>(found->second.get());
			}
			else {
				return nullptr;
			}
		}
		template <typename T> bool HasComponent()const
		{
			const auto it = m_pComponents.find(typeid(T));
			return (it != m_pComponents.end());
		}



	private:
		std::unordered_map<std::type_index, std::shared_ptr<GameComponent>> m_pComponents;
	};
}
