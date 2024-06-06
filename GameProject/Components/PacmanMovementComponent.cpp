#include "PacmanMovementComponent.h"

bdnG::PacmanMovementComponent::PacmanMovementComponent(bdnE::GameObject* owner, GridComponent* mapObject,
	float speed): GameComponent(owner)
{
	m_Speed = speed;
	m_pGridComponent = mapObject; 
	SpawnPacmanOnSpawnPoint();
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
