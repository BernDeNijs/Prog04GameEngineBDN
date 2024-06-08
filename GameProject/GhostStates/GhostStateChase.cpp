#include "GhostStateChase.h"

#include <iostream>

#include "GameObject.h"
#include <glm/glm.hpp>

#include "GhostStateScatter.h"
#include "GhostStateFrightened.h"

void bdnG::GhostStateChase::Enter(bdnE::GameObject* /*pacman*/)
{
	m_Timer = m_MaxTimer;
	std::cout << "Entered CHASE\n";
	//get the pac-men and women
	
}

void bdnG::GhostStateChase::Exit()
{
}

bdnG::GhostState* bdnG::GhostStateChase::Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent)
{
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