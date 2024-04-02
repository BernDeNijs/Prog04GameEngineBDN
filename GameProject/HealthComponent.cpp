#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner) : GameComponent(owner)
{
	m_EventData.emplace("HealthComponent", this);
}

void dae::HealthComponent::Damage(int amount)
{
	if (m_Lives <= 0) return;
	m_Lives -= amount;

	Notify("PlayerDied");
}

