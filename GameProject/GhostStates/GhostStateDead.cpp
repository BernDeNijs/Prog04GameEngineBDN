#include "GhostStateDead.h"

#include <iostream>
#include <glm/geometric.hpp>

#include "GameObject.h"
#include "GhostStateScatter.h"
#include "../Components/PickUp.h"

void bdnG::GhostStateDead::Enter(bdnE::GameObject*, std::vector< PickUp*>)
{
	std::cout << "Entered DEAD\n";
}

void bdnG::GhostStateDead::Exit(std::vector< PickUp*>)
{
}

bdnG::GhostState* bdnG::GhostStateDead::Update(bdnE::GameObject* owner, bdnE::GameObject*, bdnG::PacmanMovement* /*moveComponent*/)
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

void bdnG::GhostStateDead::Render(GhostRenderer* renderer)
{
	//For now go invisible we'll need to change our render anyway to use the spritesheet instead of seperate sprites anyway
	renderer->SetTexture("GhostDed.png");

}

void bdnG::GhostStateDead::OnNotify(const std::string& /*eventName*/,
	const std::unordered_map<std::string, std::any>& /*eventData*/)
{
}
