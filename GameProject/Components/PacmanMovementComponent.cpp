#include "PacmanMovementComponent.h"

#include <glm/detail/func_geometric.inl>

bdnG::PacmanMovementComponent::PacmanMovementComponent(bdnE::GameObject* owner, GridComponent* mapObject,
                                                       float speed): GameComponent(owner)
{
	m_Speed = speed;
	m_pGridComponent = mapObject; 
	SpawnPacmanOnSpawnPoint();
}

void bdnG::PacmanMovementComponent::Update()
{
	//check if we reached target
	auto& time = bdnE::GameTime::GetInstance();
	const float moveDistance = m_Speed * time.GetDeltaTime();
	MoveToTarget(moveDistance);

}

void bdnG::PacmanMovementComponent::SpawnPacmanOnSpawnPoint()
{
	if (m_pGridComponent == nullptr) return;
	glm::vec2 spawnPosition = { 0,0 };
	int pointsFound = 0;

	const std::vector<std::vector<GridCell>> grid = *m_pGridComponent->GetGrid();
	//Get spawnpoints
	for (const std::vector<GridCell>& column : grid)
	{
		for (const GridCell& gridCell : column)
		{
			if (gridCell.cellType == CellType::pacmanSpawn)
			{
				spawnPosition += m_pGridComponent->GetPointPosWorld(gridCell.gridIdx.first, gridCell.gridIdx.second);
				pointsFound++;
			}
		}
	}
	spawnPosition /= pointsFound;
	m_pOwner->SetLocalPosition(spawnPosition);
}

void bdnG::PacmanMovementComponent::SetMoveDirection(MoveDirections direction)
{
	m_DesiredMoveDirection = direction;
}




void bdnG::PacmanMovementComponent::MoveToTarget(float moveDistance)
{
	if (m_CurrentTarget == nullptr) 
	{
		m_CurrentTarget = FindNewTarget();
	}
	if (m_CurrentTarget == nullptr) return;

	const glm::vec2 currentPosition = m_pOwner->GetWorldTransform().Position;
	const glm::vec2 targetPosition = m_pGridComponent->GetPointPosWorld(m_CurrentTarget->gridIdx);
	const glm::vec2 vectorToTarget = targetPosition - currentPosition;
	const float distanceToTarget = glm::length(vectorToTarget);
	const glm::vec2 moveDirection = glm::normalize(targetPosition - currentPosition);

	glm::vec2 newPosition = {0,0};
	if (moveDistance < distanceToTarget)
	{
		newPosition = moveDirection * moveDistance ;		
	}
	else
	{		
		newPosition += moveDirection * distanceToTarget;
		m_CurrentTarget = FindNewTarget();
		if (m_CurrentTarget != nullptr)
		{
			const float remainingMoveDistance = moveDistance - distanceToTarget;
			MoveToTarget(remainingMoveDistance);
		}		
	}
	
	m_pOwner->SetLocalPosition( m_pOwner->GetLocalTransform().Position + newPosition);
	
}

bdnG::GridCell* bdnG::PacmanMovementComponent::FindNewTarget()
{
	//If we don't have a move direction return
	if (m_DesiredMoveDirection == MoveDirections::none) return nullptr;

	//Get current cell
	if (m_pGridComponent == nullptr) return nullptr;
	if (m_pOwner == nullptr) return nullptr;

	auto cellIdx = m_pGridComponent->GetClosestPointIdxWorld(m_pOwner->GetWorldTransform().Position);
	const std::vector<std::vector<GridCell>> grid = *m_pGridComponent->GetGrid();
	auto currentCell = grid[cellIdx.first][cellIdx.second];

	switch (m_DesiredMoveDirection)
	{
	case bdnG::MoveDirections::up:
		if (currentCell.pathUp.connectionType == ConnectionType::connected)
		{
			m_CurrentMoveDirection = MoveDirections::up;
			return currentCell.pathUp.connectedPoint;
		}

		break;
	case bdnG::MoveDirections::down:
		if (currentCell.pathDown.connectionType == ConnectionType::connected)
		{
			m_CurrentMoveDirection = MoveDirections::down;
			return currentCell.pathDown.connectedPoint;
		}
		break;
	case bdnG::MoveDirections::left:
		if (currentCell.pathLeft.connectionType == ConnectionType::connected) 
		{
			m_CurrentMoveDirection = MoveDirections::left;
			return currentCell.pathLeft.connectedPoint;
		}
		break;
	case bdnG::MoveDirections::right:
		if (currentCell.pathRight.connectionType == ConnectionType::connected)
		{
			m_CurrentMoveDirection = MoveDirections::right;
			return currentCell.pathRight.connectedPoint;
		}
		break;
	case bdnG::MoveDirections::none:
		m_CurrentMoveDirection = MoveDirections::none;
		return nullptr;
		break;
	}

	switch (m_CurrentMoveDirection)
	{
	case bdnG::MoveDirections::up:
		if (currentCell.pathUp.connectionType != ConnectionType::connected) return nullptr;
		return currentCell.pathUp.connectedPoint;
		break;
	case bdnG::MoveDirections::down:
		if (currentCell.pathDown.connectionType != ConnectionType::connected) return nullptr;
		return currentCell.pathDown.connectedPoint;
		break;
	case bdnG::MoveDirections::left:
		if (currentCell.pathLeft.connectionType != ConnectionType::connected) return nullptr;
		return currentCell.pathLeft.connectedPoint;
		break;
	case bdnG::MoveDirections::right:
		if (currentCell.pathRight.connectionType != ConnectionType::connected) return nullptr;
		return currentCell.pathRight.connectedPoint;
		break;
	case bdnG::MoveDirections::none:
		return nullptr;
		break;
	default:
		break;
	}
	return nullptr;
}
