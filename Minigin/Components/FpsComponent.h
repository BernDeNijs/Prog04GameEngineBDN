#pragma once
#include "GameComponent.h"
#include "TextComponent.h"

//#include "../GameTime.h"
//
//#include <iomanip>
//#include <sstream>

namespace dae
{
	class FpsComponent :public GameComponent
	{
	public:

		explicit FpsComponent(GameObject* owner) : GameComponent(owner) 
		{
			if (owner->HasComponent<TextComponent>() == false)
			{
				owner->AddComponent<TextComponent>();
			}

			m_pTextComponent = owner->GetComponent<TextComponent>();
		}
				
		void Update() override
		{
			const float deltaT = GameTime::GetDeltaTime();
			if (deltaT <= 0.f)
			{
				return;
			}

			m_Timer += deltaT;
			m_count++;

			if (m_Timer >= m_RefreshRate)
			{
				if (const auto sharedPtr = m_pTextComponent.lock()) {
					sharedPtr->SetText(std::format("{:.1f}", m_count / m_Timer));
				}
				m_count = 0;
				m_Timer = 0.f;
			}
		}
	private:
		float m_RefreshRate = 0.2f;
		float m_Timer{m_RefreshRate};
		int m_count{ 0 };
		std::weak_ptr<TextComponent> m_pTextComponent;

	};
}
