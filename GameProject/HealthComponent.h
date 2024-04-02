#pragma once
#include "GameComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent :public GameComponent, public Subject
	{
	public:

		explicit HealthComponent(GameObject* owner);
		void Damage(int amount);
		int GetLives() const { return m_Lives; }
	private:
		int m_Lives = 3;
	};
}