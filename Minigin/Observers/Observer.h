#pragma once
#include <string>

namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(Observer&&) = delete;

		virtual void OnNotify(const std::string& eventName, GameObject* pObject) = 0;
	};
}


