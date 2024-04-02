#include "MoveComponent.h"

dae::MoveComponent::MoveComponent(GameObject* owner)
	: GameComponent(owner)
{
}

dae::MoveComponent::MoveComponent(GameObject* owner, float speed) : MoveComponent(owner)
{
	m_Speed = speed;
}

void dae::MoveComponent::MoveInDirection(glm::vec3 direction) const
{
	glm::vec3 position = m_pOwner->GetLocalTransform().Position;
	position += GameTime::GetDeltaTime() * direction * m_Speed;
	m_pOwner->SetLocalPosition(position);
}
