#include "PickupSpawner.h"

#include "PickUp.h"

bdnG::PickupSpawner::PickupSpawner(bdnE::GameObject* owner, bdnG::Grid* mapObject): GameComponent(owner)
{
    m_Grid = mapObject;
	SpawnPickups(m_Grid);
    SpawnBonus();
}

void bdnG::PickupSpawner::Update()
{
	GameComponent::Update();
}

void bdnG::PickupSpawner::SpawnPickups(bdnG::Grid* mapObject)
{

    const std::vector<std::vector<GridCell>> grid = *mapObject->GetGrid();
    glm::vec2 scale = mapObject->GetOwner()->GetWorldTransform().Scale;
    //Get spawnpoints
    for (const std::vector<GridCell>& column : grid)
    {
        for (const GridCell& gridCell : column)
        {
            if (gridCell.cellType == CellType::pickup)
            {
                const auto pickup = m_pOwner->GetScene()->CreateGameObject(m_pOwner, false);
                pickup->AddComponent<PickUp>(ItemType::pellet);
                pickup->SetLocalPosition(mapObject->GetPointPosWorld(gridCell.gridIdx));
                pickup->SetLocalScale(scale);
            }
            if (gridCell.cellType == CellType::powerPellet)
            {
                const auto pickup = m_pOwner->GetScene()->CreateGameObject(m_pOwner, false);
                pickup->AddComponent<PickUp>(ItemType::powerPellet);
                pickup->SetLocalPosition(mapObject->GetPointPosWorld(gridCell.gridIdx));
                pickup->SetLocalScale(scale);
            }
            //if (gridCell.cellType == CellType::bonus)
            //{
            //    const auto pickup = m_pOwner->GetScene()->CreateGameObject(m_pOwner, false);
            //    pickup->AddComponent<PickUp>(ItemType::bonus);
            //    pickup->SetLocalPosition(mapObject->GetPointPosWorld(gridCell.gridIdx));
            //}
        }
    }
}

void bdnG::PickupSpawner::SpawnBonus()
{
    const std::vector<std::vector<GridCell>> grid = *m_Grid->GetGrid();
    glm::vec2 scale = m_Grid->GetOwner()->GetWorldTransform().Scale;
    //Get spawnpoints
    int positionsFound = 0;
    glm::vec2 spawnPos = { 0,0 };

    for (const std::vector<GridCell>& column : grid)
    {
        for (const GridCell& gridCell : column)
        {

            if (gridCell.cellType == CellType::bonus)
            {
                positionsFound++;
                spawnPos += m_Grid->GetPointPosWorld(gridCell.gridIdx);

                
            }
        }
    }

    if (positionsFound > 0)
    {
        spawnPos /= static_cast<float>(positionsFound);
        const auto pickup = m_pOwner->GetScene()->CreateGameObject(m_pOwner, false);
        pickup->AddComponent<PickUp>(ItemType::bonus);
        pickup->SetLocalPosition(spawnPos);
        pickup->SetLocalScale(scale);
    }
}
