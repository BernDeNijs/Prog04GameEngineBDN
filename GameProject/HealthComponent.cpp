#include "HealthComponent.h"

bdnG::HealthComponent::HealthComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
	m_EventData.emplace("HealthComponent", this);
}

void bdnG::HealthComponent::Damage(int amount)
{
	if (m_Lives <= 0) return;
	m_Lives -= amount;

	Notify("PlayerDied");
}

