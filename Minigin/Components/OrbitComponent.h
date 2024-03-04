#pragma once
#include "GameComponent.h"
#include <numbers>
#define TWO_PI std::numbers::pi *2.f

namespace dae
{
	class OrbitComponent : public dae::GameComponent
	{
	public:
		explicit OrbitComponent(GameObject* owner) : GameComponent(owner) 
		{			
		}
		explicit OrbitComponent(GameObject* owner, float radius, float speed) : OrbitComponent(owner)
		{
			m_Radius = radius;
			m_Speed = speed;
		}
		void Update() override
		{
			m_Angle += m_Speed * GameTime::GetDeltaTime();
			if (m_Angle > TWO_PI)
			{
				m_Angle -= TWO_PI;
			}
			else if (m_Angle < TWO_PI)
			{
				m_Angle += TWO_PI;
			}

			glm::vec3 position;
			position.x = cosf(m_Angle) * m_Radius;
			position.y = sinf(m_Angle) * m_Radius;
			position.z = 0.f;

			m_pOwner->SetLocalPosition(position);
		}

	private:
		float m_Radius = 0.0f;
		float m_Speed = 0.0f;
		float m_Angle = 0.0f;
	};
}


