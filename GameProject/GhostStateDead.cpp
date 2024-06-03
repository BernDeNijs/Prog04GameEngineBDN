#include "GhostStateDead.h"
#include <glm/geometric.hpp>

#include "GameObject.h"
#include "GhostStateScatter.h"
#include "RenderComponent.h"

void bdnG::GhostStateDead::Enter(bdnE::GameObject* )
{
}

void bdnG::GhostStateDead::Exit()
{
}

bdnG::GhostState* bdnG::GhostStateDead::Update(bdnE::GameObject* owner, bdnE::GameObject* )
{

	auto& time = bdnE::GameTime::GetInstance();

	//If in house TODO: add and move to late update
	auto ghostPos = owner->GetWorldTransform().Position;
	auto moveDir = m_HousePos - ghostPos;
	if (glm::length(moveDir) <= 1.0f)
	{
		return new GhostStateScatter();
	}


	//Go to house
	moveDir = glm::normalize(moveDir);
	owner->SetLocalPosition(owner->GetLocalTransform().Position + (moveDir * m_ChaseSpeed * time.GetDeltaTime()));

	return this;
}

void bdnG::GhostStateDead::Render(RenderComponent* renderer)
{
	//For now go invisible we'll need to change our render anyway to use the spritesheet instead of seperate sprites anyway
	renderer->SetTexture("GhostDed.png");

}
