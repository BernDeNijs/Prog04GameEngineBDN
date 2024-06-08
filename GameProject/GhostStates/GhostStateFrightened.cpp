#include "GhostStateFrightened.h"

#include <iostream>
#include <glm/geometric.hpp>

#include "GameObject.h"
#include "GhostStateChase.h"
#include "GhostStateDead.h"
#include "../Components/PickUp.h"

void bdnG::GhostStateFrightened::Enter(bdnE::GameObject*, std::vector< PickUp*>)
{
	m_Timer = m_MaxTimer;
	std::cout << "Entered FRIGHTENED\n";
}

void bdnG::GhostStateFrightened::Exit(std::vector< PickUp*>)
{
}

bdnG::GhostState* bdnG::GhostStateFrightened::Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent)
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
	if (glm::length(moveDir) <= 20.0f)
	{
		return new GhostStateDead();
	}


	//Handle movement
	//--get direction vector

	MoveDirections desiredMoveDirection = MoveDirections::none;
	if (abs(moveDir.x) < abs(moveDir.y))
	{
		//Horizontal
		if (moveDir.x < 0)
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
		if (moveDir.y >= 0)
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

void bdnG::GhostStateFrightened::Render(GhostRenderer* renderer)
{
	//render scared ghost
	renderer->SetTexture("GhostScared1.png");
}

void bdnG::GhostStateFrightened::OnNotify(const std::string& /*eventName*/,
	const std::unordered_map<std::string, std::any>& /*eventData*/)
{
}
