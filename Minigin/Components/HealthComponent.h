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
		}
		void Damage(int amount)
		{
			m_Hp -= amount;
			if (m_Hp <= 0 && m_Lives > 0)
			{
				m_Hp = m_MaxHp;
				m_Lives--;
				Notify("PlayerDied", m_pOwner);
			}
		}

		int GetHp() { return m_Hp; }
		int GetLives() { return m_Lives; }
	private:
		
		int m_MaxHp = 3;
		int m_Hp = m_MaxHp;
		int m_Lives = 3;
	};
}