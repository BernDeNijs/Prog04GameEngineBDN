#pragma once
#include <glm/vec2.hpp>
#include "GameComponent.h"
#include "GridComponent.h"

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
	class PacmanMovementComponent final : public bdnE::GameComponent
	{
	public:
		explicit PacmanMovementComponent(bdnE::GameObject* owner, GridComponent* mapObject, float speed = 100.f);
		void Update() override;

		void SpawnPacmanOnSpawnPoint();
		void SetMoveDirection(MoveDirections direction);
	private:
		float m_Speed{ 100.f };
		GridComponent* m_pGridComponent = nullptr;
		
		MoveDirections m_CurrentMoveDirection = MoveDirections::none;
		MoveDirections m_DesiredMoveDirection = MoveDirections::none;
		GridCell* m_CurrentTarget = nullptr;

		GridCell* FindNewTarget();
		void MoveToTarget(float moveDistance);
	};

}

