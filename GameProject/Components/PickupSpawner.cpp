#include "PickupSpawner.h"

#include "PickUp.h"

bdnG::PickupSpawner::PickupSpawner(bdnE::GameObject* owner, bdnG::Grid* mapObject): GameComponent(owner)
{
    m_Grid = mapObject;
	SpawnPickups(m_Grid);

    m_BonusTimer = 10.f;
}

void bdnG::PickupSpawner::Update()
{
    auto& time = bdnE::GameTime::GetInstance();
    if (m_BonusTimer > 0)
    {
        m_BonusTimer -= time.GetDeltaTime();
        if (m_BonusTimer <= 0)
        {
            m_BonusTimer = 0;
            PlaceBonus();
        }
    }
    
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
            if (gridCell.cellType == CellType::bonus)
            {
                if (m_BonusItem == nullptr)
                {
                    const auto pickup = m_pOwner->GetScene()->CreateGameObject(m_pOwner, false);
                    pickup->AddComponent<PickUp>(ItemType::bonus);
                    pickup->SetLocalPosition({ -1000, 0 });
                    m_BonusItem = pickup;
                }
            }
        }
    }
}

void bdnG::PickupSpawner::PlaceBonus()
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
        m_BonusItem->SetLocalPosition(spawnPos);
        m_BonusItem->SetLocalScale(scale);
    }
}
