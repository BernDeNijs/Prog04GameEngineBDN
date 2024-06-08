#pragma once
#include <glm/vec2.hpp>
#include "GameComponent.h"
#include "Grid.h"

namespace bdnG
{
	enum class MoveDirections
	{
		up,
		down,
		left,
		right,
		none
	};
	class PacmanMovement final : public bdnE::GameComponent
	{
	public:
		explicit PacmanMovement(bdnE::GameObject* owner, Grid* mapObject, float speed = 100.f);
		void Update() override;

		void SpawnPacmanOnSpawnPoint();
		void SetMoveDirection(MoveDirections direction);
	private:
		float m_Speed{ 100.f };
		Grid* m_pGridComponent = nullptr;
		
		MoveDirections m_CurrentMoveDirection = MoveDirections::none;
		MoveDirections m_DesiredMoveDirection = MoveDirections::none;
		GridCell* m_CurrentTarget = nullptr;

		GridCell* FindNewTarget();
		void MoveToTarget(float moveDistance);
	};

}

