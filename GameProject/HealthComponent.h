#pragma once
#include "GameComponent.h"
#include "Subject.h"

namespace bdnG
{
	class HealthComponent final :public bdnE::GameComponent, public bdnE::Subject
	{
	public:

		explicit HealthComponent(bdnE::GameObject* owner);
		void Damage(int amount);
		int GetLives() const { return m_Lives; }
	private:
		int m_Lives = 3;
	};
}