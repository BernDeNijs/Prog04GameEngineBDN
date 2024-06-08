#include "GhostStateScatter.h"

#include <iostream>
#include <glm/detail/func_geometric.inl>

#include "GhostStateChase.h"
#include "GhostStateFrightened.h"


void bdnG::GhostStateScatter::Enter(bdnE::GameObject* /*pacman*/)
{
	m_Timer = m_MaxTimer;
	std::cout << "Entered SCATTER\n";
}

void bdnG::GhostStateScatter::Exit()
{
}

bdnG::GhostState* bdnG::GhostStateScatter::Update(bdnE::GameObject* owner, bdnE::GameObject*, bdnG::PacmanMovement* moveComponent)
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



	//Handle movement
	//--get direction vector
	auto ghostPos = owner->GetWorldTransform().Position;
	auto moveDir = m_ScatterTarget - ghostPos;
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

void bdnG::GhostStateScatter::Render(GhostRenderer* renderer)
{
	renderer->SetTexture("GhostRed.png");
}
