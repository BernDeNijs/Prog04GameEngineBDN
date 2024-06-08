#include "GhostStateChase.h"

#include <iostream>

#include "GameObject.h"
#include <glm/glm.hpp>

#include "GhostStateScatter.h"
#include "GhostStateFrightened.h"

#include "../Components/PickUp.h"

void bdnG::GhostStateChase::Enter(bdnE::GameObject* /*pacman*/, std::vector< PickUp*> pickups)
{
	m_Timer = m_MaxTimer;
	std::cout << "Entered CHASE\n";
	//get the pac-men and women
	for (const auto& pickup : pickups)
	{
		pickup->AddObserver(this);
	}
}

void bdnG::GhostStateChase::Exit(std::vector< PickUp*> pickups)
{
	for (const auto& pickup : pickups)
	{
		pickup->RemoveObserver(this);
	}
}

bdnG::GhostState* bdnG::GhostStateChase::Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent)
{
	//Check if power pellet has been consumed
	if (m_PelletActivated)
	{
		return new GhostStateFrightened();
	}



	//Check if it's time to switch to Scatter
	auto& time = bdnE::GameTime::GetInstance();
	if (m_Timer > 0)
	{
		m_Timer -= time.GetDeltaTime();
		if (m_Timer <= 0)
		{
			return new GhostStateScatter();
		}
	}

	//Handle movement
	//--get direction vector
	const auto ghostPos = owner->GetWorldTransform().Position;
	const auto pacmanPos = pacman->GetWorldTransform().Position;
	const auto moveDir = pacmanPos - ghostPos;

	MoveDirections desiredMoveDirection = MoveDirections::none;
	if (abs(moveDir.x) > abs(moveDir.y))
	{
		//Horizontal
		if (moveDir.x >= 0)
		{
			//Right
			desiredMoveDirection = MoveDirections::right;
		}
		else
		{
			//Left
			desiredMoveDirection = MoveDirections::left;
		}
	}
	else
	{
		//Vertical
		if (moveDir.y < 0)
		{
			//Up
			desiredMoveDirection = MoveDirections::up;
		}
		else
		{
			//Down
			desiredMoveDirection = MoveDirections::down;
		}
	}
	
	moveComponent->SetMoveDirection(desiredMoveDirection);

	return this;
}

void bdnG::GhostStateChase::Render(GhostRenderer* renderer)
{
	renderer->SetTexture("GhostRed.png");
}

void bdnG::GhostStateChase::OnNotify(const std::string& /*eventName*/,
	const std::unordered_map<std::string, std::any>& /*eventData*/)
{
	m_PelletActivated = true;
}
