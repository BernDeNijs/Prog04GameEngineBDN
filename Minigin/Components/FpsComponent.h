#pragma once
#include "GameComponent.h"
#include "TextComponent.h"

#include "../GameTime.h"

#include <iomanip>
#include <sstream>

namespace dae
{
	class FpsComponent :public TextComponent
	{
	public:
		using TextComponent::TextComponent;
		
		void Update() override
		{
			const float deltaT = GameTime::GetDeltaTime();
			if (deltaT <= 0.f)
			{
				return;
			}

			m_Timer += deltaT;

			if (m_Timer >= m_RefreshRate)
			{
				m_Timer = 0.f;
				float fps{ 1.f/deltaT };



				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << fps;
				std::string s = stream.str();


				if (fps < 30)
				{
					SetColor({ 255,0,0 });
				}
				else
				{
					SetColor({ 255,255,255 });
				}
				
				//SetText(std::to_string(fps));
				SetText(s);
			}
			TextComponent::Update();
		}

	private:
		float m_RefreshRate = 1.0f;
		float m_Timer{m_RefreshRate};

	};
}
