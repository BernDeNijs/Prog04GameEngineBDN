#pragma once
#include "GameComponent.h"

namespace bdnG {
	class PowerPelletComponent : public bdnE::GameComponent
	{
	public:
		explicit PowerPelletComponent(bdnE::GameObject* owner);
		void Update()override
		{
			if (m_Timer > 0)
			{
				
				auto& time = bdnE::GameTime::GetInstance();
				m_Timer -= time.GetDeltaTime();
				if (m_Timer <= 0)
				{
					m_PoweredUp = false;
				}
			}
		}
		void PickUpPellet() { m_PoweredUp = true; m_Timer = m_MaxTime; }
		bool IsPoweredUp() const  { return m_PoweredUp; }

	private:
		bool m_PoweredUp{ false };
		float m_Timer{ 0 };
		float m_MaxTime{ 10 };
	};
}


