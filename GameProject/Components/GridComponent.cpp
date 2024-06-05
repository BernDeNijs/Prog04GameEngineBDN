#include "GridComponent.h"


bdnG::GridComponent::GridComponent(bdnE::GameObject* owner, const std::string& sourceFile,
	const std::string& texturePath) : GameComponent(owner)
{
	m_pTexture = bdnE::ResourceManager::GetInstance().LoadTexture(texturePath);
	GenerateGrid(sourceFile);
    GenerateGridConnections();
    SetTextureIds();
}



void bdnG::GridComponent::GenerateGrid(const std::string& sourceFile)
{
    const std::string levelDataString = bdnE::ResourceManager::GetInstance().LoadText(sourceFile);

    std::istringstream levelStream(levelDataString);
    std::string line;
    int rowNumber = 0; // Add a row counter
    while (std::getline(levelStream, line))
    {
        // Skip lines that start with //
        if (line.substr(0, 2) == "//")
        {
            continue;
        }

        std::vector<GridPoint> row;
        int colNumber = 0; // Add a column counter
        for (char& ch : line)
        {
            GridPoint point;
            switch (ch)
            {
            case '.':
                point.cellType = CellType::empty;
                break;
            case '-':
                point.cellType = CellType::border;
                break;
            case '=':
                point.cellType = CellType::doubleBorder;
                break;
            case 'G':
                point.cellType = CellType::ghostHouse;
                break;
            case 'E':
                point.cellType = CellType::ghostHouseEntrance;
                break;
            case '0':
                point.cellType = CellType::pickup;
                break;
            case '8':
                point.cellType = CellType::powerPellet;
                break;
            case '+':
                point.cellType = CellType::passable;
                break;
            case 'B':
                point.cellType = CellType::blinkySpawn;
                break;
            case 'P':
                point.cellType = CellType::pinkySpawn;
                break;
            case 'I':
                point.cellType = CellType::inkySpawn;
                break;
            case 'C':
                point.cellType = CellType::clydeSpawn;
                break;
            case 'W':
                point.cellType = CellType::warp;
                break;
            case 'S':
                point.cellType = CellType::bonus;
                break;
            case '@':
                point.cellType = CellType::pacmanSpawn;
                break;
            default:
                continue;
                break;
            }

            // Set the center point of the current cell
            point.center = glm::vec2(colNumber * m_CellSize.x + m_CellSize.x / 2.0f,
                rowNumber * m_CellSize.y + m_CellSize.y / 2.0f);

            row.push_back(point);
            ++colNumber;
        }
        m_Grid.push_back(row);
        ++rowNumber;
    }
}



void bdnG::GridComponent::GenerateGridConnections()
{
    // Loop over each row in the grid
    for (size_t row = 0; row < m_Grid.size(); ++row)
    {
        // Loop over each column in the grid
        for (size_t col = 0; col < m_Grid[row].size(); ++col)
        {
            // Get the current grid point
            GridPoint& point = m_Grid[row][col];

            // Check the up neighbor
            if (row > 0)
            {
                GridPoint& upNeighbor = m_Grid[row - 1][col];
                point.pathUp = CheckNeighborConnection(point.cellType,upNeighbor.cellType);
                
            }

            // Check the down neighbor
            if (row < m_Grid.size() - 1)
            {
                GridPoint& downNeighbor = m_Grid[row + 1][col];
                point.pathUp = CheckNeighborConnection(point.cellType, downNeighbor.cellType);
            }

            // Check the left neighbor
            if (col > 0)
            {
                GridPoint& leftNeighbor = m_Grid[row][col - 1];
                point.pathUp = CheckNeighborConnection(point.cellType, leftNeighbor.cellType);
            }

            // Check the right neighbor
            if (col < m_Grid[row].size() - 1)
            {
                GridPoint& rightNeighbor = m_Grid[row][col + 1];
                point.pathUp = CheckNeighborConnection(point.cellType, rightNeighbor.cellType);
            }
        }
    }
}

bdnG::GridComponent::ConnectionType bdnG::GridComponent::CheckNeighborConnection(CellType current, CellType neighbor) const
{
    if (current == CellType::empty || current == CellType::border || current == CellType::doubleBorder
        || neighbor == CellType::empty || neighbor == CellType::border || neighbor == CellType::doubleBorder)
    {
        return ConnectionType::none;
    }

    if (neighbor == CellType::ghostHouseEntrance)
    {
        return ConnectionType::ghostOnly;
    }
    return ConnectionType::connected;
}


void bdnG::GridComponent::SetTextureIds()
{
    enum class textureIds
    {
        upRightCornerDouble = 22,
        upLeftCornerDouble = 23,
        leftDoubleLine = 2,
        rightDoubleLine = 3,
        downRightCornerDouble = 26,
        downLeftCornerDouble = 27,
        downDouble = 10,
        upDouble = 12,
        up = 14,
        down = 20,
        left = 24,
        right = 25,
        empty = 44,
        pickup = 45,
        biggerPickup = 46,
        powerPellet = 47,
        upRightCorner = 22,
        upLeftCorner = 23,
        downRightCorner = 26,
        downLeftCorner = 27,
    };


    // Loop over each row in the grid
    for (size_t row = 0; row < m_Grid.size(); ++row)
    {
        // Loop over each column in the grid
        for (size_t col = 0; col < m_Grid[row].size(); ++col)
        {
            // Get the current grid point
            GridPoint& point = m_Grid[row][col];



            switch (point.cellType)
            {
            case CellType::passable:
            case CellType::bonus:
            case CellType::ghostHouse:
            case CellType::warp:
            case CellType::blinkySpawn:
            case CellType::pinkySpawn:
            case CellType::inkySpawn:
            case CellType::clydeSpawn:
            case CellType::pacmanSpawn:
            case CellType::empty:
                point.textureId = static_cast<int>(textureIds::empty);
                break;
            case CellType::pickup:
                point.textureId = static_cast<int>(textureIds::pickup);
            case CellType::ghostHouseEntrance:
                point.textureId = static_cast<int>(textureIds::biggerPickup);
                break;
            case CellType::powerPellet:
                point.textureId = static_cast<int>(textureIds::powerPellet);
                break;
            default:
                break;
            }


            if (point.cellType == CellType::border ||
                point.cellType == CellType::doubleBorder)
            {
                bool upNeighborPassable = false;
                bool downNeighborPassable = false;
                bool leftNeighborPassable = false;
                bool rightNeighborPassable = false;


                // Check the up neighbor
                if (row > 0)
                {
                    GridPoint& upNeighbor = m_Grid[row - 1][col];
                    if ((upNeighbor.cellType != CellType::empty) &&
                        (upNeighbor.cellType != CellType::border) &&
                        (upNeighbor.cellType != CellType::doubleBorder)
                        )
                    {
                        upNeighborPassable = true;
                    }
                }

                // Check the down neighbor
                if (row < m_Grid.size() - 1)
                {
                    GridPoint& downNeighbor = m_Grid[row + 1][col];
                    if (downNeighbor.cellType != CellType::empty &&
                        (downNeighbor.cellType != CellType::border) &&
                        (downNeighbor.cellType != CellType::doubleBorder)
                        )
                    {
                        downNeighborPassable = true;
                    }

                }

                // Check the left neighbor
                if (col > 0)
                {
                    GridPoint& leftNeighbor = m_Grid[row][col - 1];
                    if (leftNeighbor.cellType != CellType::empty &&
                        (leftNeighbor.cellType != CellType::border) &&
                        (leftNeighbor.cellType != CellType::doubleBorder)
                        )
                    {
                        leftNeighborPassable = true;
                    }
                }

                // Check the right neighbor
                if (col < m_Grid[row].size() - 1)
                {
                    GridPoint& rightNeighbor = m_Grid[row][col + 1];
                    if (rightNeighbor.cellType != CellType::empty &&
                        (rightNeighbor.cellType != CellType::border) &&
                        (rightNeighbor.cellType != CellType::doubleBorder)
                        )
                    {
                        rightNeighborPassable = true;
                    }
                }

                if (upNeighborPassable && rightNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::upRightCorner);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::upRightCornerDouble);
                    }
                    
                }
                else if (rightNeighborPassable && downNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::downRightCorner);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::downRightCornerDouble);
                    }
                }
                else if (downNeighborPassable && leftNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::downLeftCorner);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::downLeftCornerDouble);
                    }
                }
                else if (leftNeighborPassable && upNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::upLeftCorner);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::upLeftCornerDouble);
                    }
                }
                else if (upNeighborPassable)
                {

                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::up);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::upDouble);
                    }
                }
                else if (downNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::down);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::downDouble);
                    }
                }
                else if (leftNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::left);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::leftDoubleLine);
                    }
                }
                else if (rightNeighborPassable)
                {
                    if (point.cellType == CellType::border)
                    {
                        point.textureId = static_cast<int>(textureIds::right);
                    }
                    else
                    {
                        point.textureId = static_cast<int>(textureIds::rightDoubleLine);
                    }
                }
            }            
        
        }
    }
}


void bdnG::GridComponent::Render() const
{
    auto& renderer = bdnE::Renderer::GetInstance();
    bdnE::Transform pointTransform = m_pOwner->GetWorldTransform();
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = static_cast<int>(m_CellSize.x);
    srcRect.h = static_cast<int>(m_CellSize.y);


    for (size_t row = 0; row < m_Grid.size(); ++row)
    {
        // Loop over each column in the grid
        for (size_t col = 0; col < m_Grid[row].size(); ++col)
        {
            // Get the current grid point
            const GridPoint point = m_Grid[row][col];
            
            pointTransform.Position = m_pOwner->GetWorldTransform().Position + (GetPointPos(static_cast<int>(row), static_cast<int>(col)) * m_pOwner->GetWorldTransform().Scale);

            srcRect.x = (point.textureId % 16) * static_cast<int>(m_CellSize.x+1);
            srcRect.y = (point.textureId / 16) * static_cast<int>(m_CellSize.y+1);

            renderer.RenderTexture(*m_pTexture, pointTransform, &srcRect);
        }
    }







}

glm::vec2 bdnG::GridComponent::GetPointPos(int row, int column) const
{
    

    float x = column * m_CellSize.x;
    float y = row * m_CellSize.y;

    return { x, y };
}

glm::vec2 bdnG::GridComponent::GetPointPosWorld(int row, int column) const
{
    auto xy = GetPointPos(row, column);

    //take into account world pos
    const auto transform = m_pOwner->GetWorldTransform();
    xy.x += transform.Position.x;
    xy.y += transform.Position.y;


    return xy;
}

std::pair<int, int> bdnG::GridComponent::GetClosestPointIdx(glm::vec2 position) const
{
    
    float xPos = position.x;
    float yPos = position.y;

    int column = static_cast<int>(round(xPos / m_CellSize.x));
    int row = static_cast<int>(round(yPos / m_CellSize.y));
    return std::make_pair(row, column);
}

std::pair<int, int> bdnG::GridComponent::GetClosestPointIdxWorld(glm::vec2 position) const
{
    float xPos = position.x;
    float yPos = position.y;

    //take into account world pos
    const auto transform = m_pOwner->GetWorldTransform();
    xPos -= transform.Position.x;
    yPos -= transform.Position.y;


    int column = static_cast<int>(round(xPos / m_CellSize.x));
    int row = static_cast<int>(round(yPos / m_CellSize.y));
    return std::make_pair(row, column);
}
