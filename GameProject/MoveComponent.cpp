#include "MoveComponent.h"

bdnG::MoveComponent::MoveComponent(bdnE::GameObject* owner)
	: GameComponent(owner)
{
}

bdnG::MoveComponent::MoveComponent(bdnE::GameObject* owner, float speed) : MoveComponent(owner)
{
	m_Speed = speed;
}

void bdnG::MoveComponent::MoveInDirection(glm::vec3 direction) const
{
	auto& time = bdnE::GameTime::GetInstance();


	glm::vec3 position = m_pOwner->GetLocalTransform().Position;
	position += time.GetDeltaTime() * direction * m_Speed;
	m_pOwner->SetLocalPosition(position);
}
