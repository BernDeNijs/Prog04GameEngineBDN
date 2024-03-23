#pragma once
#include <memory>
#include <vector>

#include "Observer.h"
namespace dae
{
	class GameObject;
	class Subject
	{
	public:
		explicit Subject() = default;

		void AddObserver(Observer* observer)
		{
			m_pObservers.emplace_back(observer);
		}
		void RemoveObserver(Observer* observer)
		{
			if (const auto it = std::find(m_pObservers.begin(), m_pObservers.end(), observer); 
				it != m_pObservers.end())
			{
				m_pObservers.erase(it);
			}
		}

		void Notify(const std::string& eventName, GameObject* pGameObject)
		{
			for (const auto& observer : m_pObservers)
			{
				observer->OnNotify(eventName, pGameObject); 
			}
		}

	private:
		std::vector<Observer*> m_pObservers{};
	};
}


