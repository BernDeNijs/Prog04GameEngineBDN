#include "OrbitComponent.h"

dae::OrbitComponent::OrbitComponent(GameObject* owner) : GameComponent(owner)
{
}

dae::OrbitComponent::OrbitComponent(GameObject* owner, float radius, float speed) : OrbitComponent(owner)
{
	m_Radius = radius;
	m_Speed = speed;
}

void dae::OrbitComponent::Update()
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
