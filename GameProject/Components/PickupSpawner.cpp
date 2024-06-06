#include "PickupSpawner.h"

bdnG::PickupSpawner::PickupSpawner(bdnE::GameObject* owner, bdnG::GridComponent* mapObject): GameComponent(owner)
{
	SpawnPickups(mapObject);
}

void bdnG::PickupSpawner::SpawnPickups(bdnG::GridComponent* mapObject)
{

    const std::vector<std::vector<GridCell>> grid = *mapObject->GetGrid();
    //Get spawnpoints
    for (const std::vector<GridCell>& column : grid)
    {
        for (const GridCell& gridCell : column)
        {
            if (gridCell.cellType == CellType::pickup)
            {
                /*auto pickup =*/ m_pOwner->GetScene()->CreateGameObject(m_pOwner, false);
            }
            if (gridCell.cellType == CellType::powerPellet)
            {

            }
            if (gridCell.cellType == CellType::bonus)
            {

            }
        }
    }
}
