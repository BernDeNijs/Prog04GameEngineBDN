#include "GhostStateFrightened.h"

#include <glm/geometric.hpp>

#include "GameObject.h"
#include "GhostStateChase.h"
#include "GhostStateDead.h"
#include "RenderComponent.h"

void bdnG::GhostStateFrightened::Enter(bdnE::GameObject* )
{
	m_Timer = m_MaxTimer;
}

void bdnG::GhostStateFrightened::Exit()
{
}

bdnG::GhostState* bdnG::GhostStateFrightened::Update(bdnE::GameObject* owner, bdnE::GameObject* pacman)
{
	//Check if it's time to switch to chase
	auto& time = bdnE::GameTime::GetInstance();
	if (m_Timer > 0)
	{
		m_Timer -= time.GetDeltaTime();
		if (m_Timer <= 0)
		{
			return new GhostStateChase();
		}
	}

	//If colliding with pacman TODO: add and move to late update
	auto ghostPos = owner->GetWorldTransform().Position;
	auto pacmanPos = pacman->GetWorldTransform().Position;
	auto moveDir = pacmanPos - ghostPos;
	if (glm::length(moveDir) <= 1.0f)
	{
		return new GhostStateDead();
	}
	

	//Flee pacman

	
	moveDir = glm::normalize(moveDir);
	owner->SetLocalPosition(owner->GetLocalTransform().Position - (moveDir * m_ChaseSpeed * time.GetDeltaTime()));

	return this;
}

void bdnG::GhostStateFrightened::Render(RenderComponent* renderer)
{
	//render scared ghost
	renderer->SetTexture("GhostScared1.png");
}
