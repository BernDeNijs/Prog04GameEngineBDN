#include "Grid.h"


bdnG::Grid::Grid(bdnE::GameObject* owner, const std::string& sourceFile,
                 const std::string& texturePath) : GameComponent(owner)
{
	m_pTexture = bdnE::ResourceManager::GetInstance().LoadTexture(texturePath);
	GenerateGrid(sourceFile);
    GenerateGridConnections();
    SetTextureIds();
}



void bdnG::Grid::GenerateGrid(const std::string& sourceFile)
{
    const std::string levelDataString = bdnE::ResourceManager::GetInstance().LoadText(sourceFile);
    std::vector<std::vector<GridCell>>& grid = *m_Grid;

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

        std::vector<GridCell> row;
        int colNumber = 0; // Add a column counter
        for (char& ch : line)
        {
            GridCell point;
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
            /*point.center = glm::vec2(colNumber * m_CellSize.x + m_CellSize.x / 2.0f,
                rowNumber * m_CellSize.y + m_CellSize.y / 2.0f);*/
            point.gridIdx = { rowNumber,colNumber };
            row.push_back(point);
            ++colNumber;
        }
        grid.push_back(row);
        ++rowNumber;
    }
}



void bdnG::Grid::GenerateGridConnections()
{
    std::vector<std::vector<GridCell>>& grid = *m_Grid;
    // Loop over each row in the grid
    for (size_t row = 0; row < grid.size(); ++row)
    {
        // Loop over each column in the grid
        for (size_t col = 0; col < grid[row].size(); ++col)
        {
            // Get the current grid point
            GridCell& point = grid[row][col];

            // Check the up neighbor
            if (row > 0)
            {
                GridCell& upNeighbor = grid[row - 1][col];
                point.pathUp = GridConnection{ CheckNeighborConnection(point.cellType,upNeighbor.cellType),&upNeighbor };
                
            }

            // Check the down neighbor
            if (row < grid.size() - 1)
            {
                GridCell& downNeighbor = grid[row + 1][col];
                point.pathDown = GridConnection{ CheckNeighborConnection(point.cellType,downNeighbor.cellType),&downNeighbor };

            }

            // Check the left neighbor
            if (col > 0)
            {
                GridCell& leftNeighbor = grid[row][col - 1];
                point.pathLeft = GridConnection{ CheckNeighborConnection(point.cellType,leftNeighbor.cellType),&leftNeighbor };
            }

            // Check the right neighbor
            if (col < grid[row].size() - 1)
            {
                GridCell& rightNeighbor = grid[row][col + 1];
                point.pathRight = GridConnection{ CheckNeighborConnection(point.cellType,rightNeighbor.cellType),&rightNeighbor };
            }
        }
    }
}

bdnG::ConnectionType bdnG::Grid::CheckNeighborConnection(CellType current, CellType neighbor) const
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


void bdnG::Grid::SetTextureIds()
{
    enum class textureIds
    {
        empty = 44,
        pickup = 45,
        biggerPickup = 46,
        powerPellet = 47,

        ghostHouseDoor = 43,
        up = 14,
        upDouble = 12,
        down = 20,
        downDouble = 10,
        left = 24,
        leftDoubleLine = 2,
        right = 25,
        rightDoubleLine = 3,

        upRightCorner = 41,
        upRightCornerDouble = 41,
        upLeftCorner = 40,
        upLeftCornerDouble = 40,
        downRightCorner = 39,      
        downRightCornerDouble = 39,
        downLeftCorner = 38,
        downLeftCornerDouble = 38,
        
        
        
        
        
        
        
        
        
        
        
    };
    std::vector<std::vector<GridCell>>& grid = *m_Grid;

    // Loop over each row in the grid
    for (size_t row = 0; row < grid.size(); ++row)
    {
        // Loop over each column in the grid
        for (size_t col = 0; col < grid[row].size(); ++col)
        {
            // Get the current grid point
            GridCell& point = grid[row][col];



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
                point.textureId = static_cast<int>(textureIds::empty);
                break;
            case CellType::ghostHouseEntrance:
                point.textureId = static_cast<int>(textureIds::ghostHouseDoor);
                break;
            case CellType::powerPellet:
                point.textureId = static_cast<int>(textureIds::empty);
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
                    GridCell& upNeighbor = grid[row - 1][col];
                    if (static_cast<int>(upNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
                    {
                        upNeighborPassable = true;
                    }
                }

                // Check the down neighbor
                if (row < grid.size() - 1)
                {
                    GridCell& downNeighbor = grid[row + 1][col];
                    if (static_cast<int>(downNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
                    {
                        downNeighborPassable = true;
                    }

                }

                // Check the left neighbor
                if (col > 0)
                {
                    GridCell& leftNeighbor = grid[row][col - 1];
                    if (static_cast<int>(leftNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
                    {
                        leftNeighborPassable = true;
                    }
                }

                // Check the right neighbor
                if (col < grid[row].size() - 1)
                {
                    GridCell& rightNeighbor = grid[row][col + 1];
                    if (static_cast<int>(rightNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
                    {
                        rightNeighborPassable = true;
                    }
                }

                if (upNeighborPassable && rightNeighborPassable)
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
                else if (rightNeighborPassable && downNeighborPassable)
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
                else if (downNeighborPassable && leftNeighborPassable)
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
                else if (leftNeighborPassable && upNeighborPassable)
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
                else
                {
                    //Check inner corners
                    if (row > 0 && col > 0) //top left checkable
                    {
                        GridCell& upLeftNeighbor = grid[row - 1][col-1];
                        if (static_cast<int>(upLeftNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
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
                    }
                    if (row < grid.size() - 1 && col < grid[row].size() - 1) //bottom right
                    {
                        GridCell& downRightNeighbor = grid[row + 1][col + 1];
                        if (static_cast<int>(downRightNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
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
                    }
                    if (row > 0 && col < grid[row].size() - 1) //top right checkable
                    {
                        GridCell& upRightNeighbor = grid[row - 1][col + 1];
                        if (static_cast<int>(upRightNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
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
                    }
                    if (row < grid.size() - 1 && col > 0) //bottom left
                    {
                        GridCell& downLeftNeighbor = grid[row + 1][col - 1];
                        if (static_cast<int>(downLeftNeighbor.cellType) > static_cast<int>(CellType::doubleBorder)) //if not impassable
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
                    }
                }
            }            
        
        }
    }
}


void bdnG::Grid::Render() const
{
    auto& renderer = bdnE::Renderer::GetInstance();
    bdnE::Transform pointTransform = m_pOwner->GetWorldTransform();
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = static_cast<int>(m_CellSize.x);
    srcRect.h = static_cast<int>(m_CellSize.y);
    const std::vector<std::vector<GridCell>>& grid = *m_Grid;

    for (size_t row = 0; row < grid.size(); ++row)
    {
        // Loop over each column in the grid
        for (size_t col = 0; col < grid[row].size(); ++col)
        {
            // Get the current grid point
            const GridCell point = grid[row][col];
            
            pointTransform.Position = m_pOwner->GetWorldTransform().Position + (GetPointPos(static_cast<int>(row), static_cast<int>(col)) * m_pOwner->GetWorldTransform().Scale);

            srcRect.x = (point.textureId % 16) * static_cast<int>(m_CellSize.x+1);
            srcRect.y = (point.textureId / 16) * static_cast<int>(m_CellSize.y+1);

            renderer.RenderTexture(*m_pTexture, pointTransform, &srcRect);
        }
    }







}

glm::vec2 bdnG::Grid::GetPointPos(int row, int column) const
{
    

    float x = column * m_CellSize.x;
    float y = row * m_CellSize.y;

    return { x, y };
}

glm::vec2 bdnG::Grid::GetPointPos(std::pair<int, int> idx) const
{
    return GetPointPos(idx.first, idx.second);
}

glm::vec2 bdnG::Grid::GetPointPosWorld(int row, int column) const
{
    auto xy = GetPointPos(row, column);

    //take into account world pos
    const auto transform = m_pOwner->GetWorldTransform();

    xy.x += m_CellSize.x * 0.5f;
    xy.y += m_CellSize.y * 0.5f;

    xy.x *= transform.Scale.x;
    xy.y *= transform.Scale.y;

    xy.x += transform.Position.x;
    xy.y += transform.Position.y;

    return xy;
}

glm::vec2 bdnG::Grid::GetPointPosWorld(std::pair<int, int> idx) const
{
    return GetPointPosWorld(idx.first, idx.second);
}

std::pair<int, int> bdnG::Grid::GetClosestPointIdx(glm::vec2 position) const
{
    
    float xPos = position.x;
    float yPos = position.y;

    int column = static_cast<int>(round(xPos / m_CellSize.x));
    int row = static_cast<int>(round(yPos / m_CellSize.y));
    return std::make_pair(row, column);
}

std::pair<int, int> bdnG::Grid::GetClosestPointIdxWorld(glm::vec2 position) const
{
    auto xy = position;

    //take into account world pos
    const auto transform = m_pOwner->GetWorldTransform();


    xy.x -= transform.Position.x;
    xy.y -= transform.Position.y;

    xy.x -= m_CellSize.x ;
    xy.y -= m_CellSize.y ;

    xy.x /= transform.Scale.x;
    xy.y /= transform.Scale.y;
    
    return GetClosestPointIdx(xy);
}
