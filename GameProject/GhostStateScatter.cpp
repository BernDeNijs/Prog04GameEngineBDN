#include "GhostStateScatter.h"
#include "GameObject.h"
#include <glm/glm.hpp>

#include "GhostStateChase.h"
#include "GhostStateFrightened.h"
#include "PowerPelletComponent.h"
#include "RenderComponent.h"

void bdnG::GhostStateScatter::Enter(bdnE::GameObject* pacman)
{
	m_PelletComp = pacman->GetComponent<PowerPelletComponent>();
	m_Timer = m_MaxTimer;
}

void bdnG::GhostStateScatter::Exit()
{
}

bdnG::GhostState* bdnG::GhostStateScatter::Update(bdnE::GameObject* owner, bdnE::GameObject* )
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
	auto moveDir = m_ScatterTarget - ghostPos;
	moveDir = glm::normalize(moveDir);
	owner->SetLocalPosition(owner->GetLocalTransform().Position +( moveDir * m_ChaseSpeed* time.GetDeltaTime()));
	
	return this;
}

void bdnG::GhostStateScatter::Render(RenderComponent* renderer)
{
	//Render spooky ghost
	renderer->SetTexture("GhostRed.png");
}
