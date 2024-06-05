#pragma once
#include <glm/vec2.hpp>

#include "Command.h"
#include "Command.h"
#include "GameComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace bdnG
{
	class GridComponent final : public bdnE::GameComponent
	{

		enum class CellType
		{
			empty,
			border,
			doubleBorder,
			passable,
			pickup,
			bonus,
			powerPellet,
			ghostHouse,
			ghostHouseEntrance,
			warp,
			blinkySpawn,
			pinkySpawn,
			inkySpawn,
			clydeSpawn,
			pacmanSpawn
		};
		enum class ConnectionType
		{
			none,
			connected,
			ghostOnly,
		};

		struct GridPoint
		{
			glm::vec2 center = glm::vec2{ 0,0 };

			ConnectionType pathUp = ConnectionType::none;
			ConnectionType pathDown = ConnectionType::none;
			ConnectionType pathLeft = ConnectionType::none;
			ConnectionType pathRight = ConnectionType::none;

			CellType cellType = CellType::empty;
			int textureId = 0; //16*3 ; 48 total; maxId = 47
		};

	public:
		explicit GridComponent(bdnE::GameObject* owner, const std::string& sourceFile, const std::string& texturePath);

		glm::vec2 GetPointPos(int row, int column) const;
		glm::vec2 GetPointPosWorld(int row, int column) const;
		std::pair<int, int> GetClosestPointIdx(glm::vec2 position) const;
		std::pair<int, int> GetClosestPointIdxWorld(glm::vec2 position) const;

		void Render() const override;
	private:
		std::shared_ptr<bdnE::Texture2D> m_pTexture;
		std::vector<std::vector<GridPoint>> m_Grid = std::vector<std::vector<GridPoint>>{};
		void GenerateGrid(const std::string& sourceFile);
		void GenerateGridConnections();
		ConnectionType CheckNeighborConnection(CellType current, CellType neighbor) const;
		void SetTextureIds();

		glm::vec2 m_CellSize{ 8.f,8.f };
	};

}


