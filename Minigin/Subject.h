#pragma once
#include <memory>
#include <vector>

#include "Observer.h"
namespace bdnE
{
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
			auto it = std::remove(m_pObservers.begin(), m_pObservers.end(), observer);
			if (it != m_pObservers.end())
			{
				m_pObservers.erase(it, m_pObservers.end());
			}
		}

		void Notify(const std::string& eventName)
		{
			for (const auto& observer : m_pObservers)
			{
				observer->OnNotify(eventName, m_EventData);
			}
		}
	protected:
		std::unordered_map<std::string, std::any> m_EventData;

	private:
		std::vector<Observer*> m_pObservers{};
		
	};
}


