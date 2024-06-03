#include "GhostStateChase.h"

#include "GameObject.h"
#include <glm/glm.hpp>

#include "GhostStateScatter.h"
#include "GhostStateFrightened.h"
#include "PowerPelletComponent.h"
#include "RenderComponent.h"

void bdnG::GhostStateChase::Enter(bdnE::GameObject* pacman)
{
	m_PelletComp = pacman->GetComponent<PowerPelletComponent>();
	m_Timer = m_MaxTimer;
}

void bdnG::GhostStateChase::Exit()
{
}

bdnG::GhostState* bdnG::GhostStateChase::Update(bdnE::GameObject* owner, bdnE::GameObject* pacman)
{
	//Check if packman picked up a powerPellet

	if (m_PelletComp != nullptr)
	{
		if (m_PelletComp->IsPoweredUp())
		{
			return new GhostStateFrightened();
		}
	}

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



	//Handle movement
	//--get direction vector
	auto ghostPos = owner->GetWorldTransform().Position;
	auto pacmanPos = pacman->GetWorldTransform().Position;
	auto moveDir = pacmanPos - ghostPos;
	moveDir = glm::normalize(moveDir);
	owner->SetLocalPosition(owner->GetLocalTransform().Position + (moveDir * m_ChaseSpeed * time.GetDeltaTime()));

	return this;
}

void bdnG::GhostStateChase::Render(RenderComponent* renderer)
{
	renderer->SetTexture("GhostRed.png");
}
