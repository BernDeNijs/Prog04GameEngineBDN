#include "PacmanMovement.h"

#include <queue>
#include <set>
#include <glm/detail/func_geometric.inl>

bdnG::PacmanMovement::PacmanMovement(bdnE::GameObject* owner, Grid* mapObject, CellType spawnPoint, bool useGhostTypeMovement , float speed ): GameComponent(owner)
{
	m_Speed = speed;
	m_pGridComponent = mapObject; 
	m_SpawnPoint = spawnPoint;
	m_GhostTypeMovement = useGhostTypeMovement;
	SpawnOnSpawnPoint();
}

void bdnG::PacmanMovement::Update()
{
	//check if we reached target
	auto& time = bdnE::GameTime::GetInstance();
	const float moveDistance = m_Speed * time.GetDeltaTime();
	MoveToTarget(moveDistance);

}

void bdnG::PacmanMovement::SpawnOnSpawnPoint() const
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
			if (gridCell.cellType == m_SpawnPoint)
			{
				spawnPosition += m_pGridComponent->GetPointPosWorld(gridCell.gridIdx.first, gridCell.gridIdx.second);
				pointsFound++;
			}
		}
	}
	spawnPosition /= pointsFound;
	m_pOwner->SetLocalPosition(spawnPosition);
}

void bdnG::PacmanMovement::SetMoveDirection(MoveDirections direction)
{
	m_DesiredMoveDirection = direction;
}




void bdnG::PacmanMovement::MoveToTarget(float moveDistance)
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

bdnG::GridCell* bdnG::PacmanMovement::FindNewTarget()
{
	//If we don't have a move direction return
	if (m_DesiredMoveDirection == MoveDirections::none) return nullptr;

	//Get current cell
	if (m_pGridComponent == nullptr) return nullptr;
	if (m_pOwner == nullptr) return nullptr;

	auto cellIdx = m_pGridComponent->GetClosestPointIdxWorld(m_pOwner->GetWorldTransform().Position);
	const std::vector<std::vector<GridCell>> grid = *m_pGridComponent->GetGrid();
	auto& currentCell = grid[cellIdx.first][cellIdx.second];

	switch (m_DesiredMoveDirection)
	{
	case bdnG::MoveDirections::up:
		if (currentCell.pathUp.connectionType == ConnectionType::connected)
		{
			m_CurrentMoveDirection = MoveDirections::up;
			return currentCell.pathUp.connectedPoint;
		}
		//--added logic for ghost movement
		if (m_GhostTypeMovement)
		{
			if (currentCell.pathUp.connectionType == ConnectionType::ghostOnly)
			{
				m_CurrentMoveDirection = MoveDirections::up;
				return currentCell.pathUp.connectedPoint;
			}
			else
			{
				return FindClosestTargetWithDirection(MoveDirections::up, m_CurrentMoveDirection, currentCell);
			}				
		}
		//--
		break;
	case bdnG::MoveDirections::down:
		if (currentCell.pathDown.connectionType == ConnectionType::connected)
		{
			m_CurrentMoveDirection = MoveDirections::down;
			return currentCell.pathDown.connectedPoint;
		}
		if (m_GhostTypeMovement)
		{
			if (currentCell.pathUp.connectionType == ConnectionType::ghostOnly)
			{
				m_CurrentMoveDirection = MoveDirections::up;
				return currentCell.pathUp.connectedPoint;
			}
			else
			{
				return FindClosestTargetWithDirection(MoveDirections::down, m_CurrentMoveDirection, currentCell);
			}
		}
		break;
	case bdnG::MoveDirections::left:
		if (currentCell.pathLeft.connectionType == ConnectionType::connected) 
		{
			m_CurrentMoveDirection = MoveDirections::left;
			return currentCell.pathLeft.connectedPoint;
		}
		if (m_GhostTypeMovement)
		{
			if (currentCell.pathUp.connectionType == ConnectionType::ghostOnly)
			{
				m_CurrentMoveDirection = MoveDirections::up;
				return currentCell.pathUp.connectedPoint;
			}
			else
			{
				return FindClosestTargetWithDirection(MoveDirections::left, m_CurrentMoveDirection, currentCell);
			}
		}
		break;
	case bdnG::MoveDirections::right:
		if (currentCell.pathRight.connectionType == ConnectionType::connected)
		{
			m_CurrentMoveDirection = MoveDirections::right;
			return currentCell.pathRight.connectedPoint;
		}
		if (m_GhostTypeMovement)
		{
			if (currentCell.pathUp.connectionType == ConnectionType::ghostOnly)
			{
				m_CurrentMoveDirection = MoveDirections::up;
				return currentCell.pathUp.connectedPoint;
			}
			else
			{
				return FindClosestTargetWithDirection(MoveDirections::right, m_CurrentMoveDirection, currentCell);
			}
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

bdnG::GridCell* bdnG::PacmanMovement::FindClosestTargetWithDirection(MoveDirections direction, bdnG::MoveDirections currentDirection, bdnG::GridCell currentCell)
{

	if (m_pGridComponent == nullptr) return nullptr;

	// To keep track of visited cells
	std::set<std::pair<int, int>> visited;

	// Queue for BFS
	std::queue<GridCell*> queue;
	queue.push(&currentCell);

	while (!queue.empty())
	{
		GridCell* cell = queue.front();
		queue.pop();

		// Check if cell has already been visited
		auto cellIdx = cell->gridIdx;
		if (visited.find(cellIdx) != visited.end())
		{
			continue;
		}
		visited.insert(cellIdx);

		// Check if this cell has a path in the desired direction
		switch (direction)
		{
		case MoveDirections::up:
			if (cell->pathUp.connectionType == ConnectionType::connected || cell->pathUp.connectionType == ConnectionType::ghostOnly)
			{
				return cell;
			}
			break;
		case MoveDirections::down:
			if (cell->pathDown.connectionType == ConnectionType::connected || cell->pathDown.connectionType == ConnectionType::ghostOnly)
			{
				return cell;
			}
			break;
		case MoveDirections::left:
			if (cell->pathLeft.connectionType == ConnectionType::connected || cell->pathLeft.connectionType == ConnectionType::ghostOnly)
			{
				return cell;
			}
			break;
		case MoveDirections::right:
			if (cell->pathRight.connectionType == ConnectionType::connected || cell->pathRight.connectionType == ConnectionType::ghostOnly)
			{
				return cell;
			}
			break;
		default:
			break;
		}

		// Add all connected cells to the queue, except for the opposite direction
		if ((cell->pathUp.connectionType == ConnectionType::connected || 
			cell->pathUp.connectionType == ConnectionType::ghostOnly) && 
			currentDirection != MoveDirections::down && 
			direction != MoveDirections::down
			)
		{
			queue.push(cell->pathUp.connectedPoint);
		}
		if ((cell->pathDown.connectionType == ConnectionType::connected || 
			cell->pathDown.connectionType == ConnectionType::ghostOnly) && 
			currentDirection != MoveDirections::up &&
			direction != MoveDirections::up)
		{
			queue.push(cell->pathDown.connectedPoint);
		}
		if ((cell->pathLeft.connectionType == ConnectionType::connected || 
			cell->pathLeft.connectionType == ConnectionType::ghostOnly) && 
			currentDirection != MoveDirections::right &&
			direction != MoveDirections::right)
		{
			queue.push(cell->pathLeft.connectedPoint);
		}
		if ((cell->pathRight.connectionType == ConnectionType::connected || 
			cell->pathRight.connectionType == ConnectionType::ghostOnly) && 
			currentDirection != MoveDirections::left &&
			direction != MoveDirections::left)
		{
			queue.push(cell->pathRight.connectedPoint);
		}
	}

	return nullptr;
}
