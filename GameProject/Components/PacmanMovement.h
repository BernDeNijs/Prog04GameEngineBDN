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
		explicit PacmanMovement(bdnE::GameObject* owner, Grid* mapObject, CellType spawnPoint, bool useGhostTypeMovement = false , float speed = 100.f);
		void Update() override;

		void SpawnOnSpawnPoint() const;
		void SetMoveDirection(MoveDirections direction);
		void SetSpeed(float speed) { m_Speed = speed; }
	private:
		float m_Speed{ 100.f };
		Grid* m_pGridComponent = nullptr;
		
		MoveDirections m_CurrentMoveDirection = MoveDirections::none;
		MoveDirections m_DesiredMoveDirection = MoveDirections::none;
		GridCell* m_CurrentTarget = nullptr;

		CellType m_SpawnPoint;
		bool m_GhostTypeMovement;

		GridCell* FindNewTarget();
		GridCell* FindClosestTargetWithDirection(MoveDirections direction, MoveDirections currentDirection, GridCell currentCell);
		void MoveToTarget(float moveDistance);


	};

}

