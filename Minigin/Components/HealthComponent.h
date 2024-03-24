#pragma once
#include "GameComponent.h"
#include "../Observers/Subject.h"

namespace dae
{
	class HealthComponent :public GameComponent, public Subject
	{
	public:

		explicit HealthComponent(GameObject* owner) : GameComponent(owner)
		{
			m_EventData.emplace("HealthComponent", this);
		}
		void Damage(int amount)
		{
			if (m_Lives <= 0) return;
			m_Lives -= amount;
			
			Notify("PlayerDied");
		}

		int GetLives() { return m_Lives; }
	private:
		
		int m_Lives = 3;
		
	};
}