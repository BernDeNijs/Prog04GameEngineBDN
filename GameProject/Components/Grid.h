#pragma once
#include <glm/vec2.hpp>

#include "Command.h"
#include "Command.h"
#include "GameComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace bdnG
{
	enum class CellType
	{
		empty,
		ghostHouse,
		ghostHouseEntrance,
		pinkySpawn,
		inkySpawn,
		clydeSpawn,
		border,
		doubleBorder,
		passable,
		pickup,
		bonus,
		powerPellet,
		warp,
		blinkySpawn,
		pacmanSpawn
	};
	enum class ConnectionType
	{
		none,
		connected,
		ghostOnly,
	};

	struct GridCell;
	struct GridConnection
	{
		ConnectionType connectionType = ConnectionType::none;
		GridCell* connectedPoint = nullptr;
	};

	struct GridCell
	{
		std::pair<int, int> gridIdx = { 0,0 };
		GridConnection pathUp = GridConnection();
		GridConnection pathDown = GridConnection();
		GridConnection pathLeft = GridConnection();
		GridConnection pathRight = GridConnection();

		CellType cellType = CellType::empty;
		int textureId = 0; //16*3 ; 48 total; maxId = 47
	};
	class Grid final : public bdnE::GameComponent
	{
	public:
		explicit Grid(bdnE::GameObject* owner, const std::string& sourceFile, const std::string& texturePath);

		glm::vec2 GetPointPos(int row, int column) const;
		glm::vec2 GetPointPos(std::pair<int, int>) const;
		glm::vec2 GetPointPosWorld(int row, int column) const;
		glm::vec2 GetPointPosWorld(std::pair<int, int>) const;
		std::pair<int, int> GetClosestPointIdx(glm::vec2 position) const;
		std::pair<int, int> GetClosestPointIdxWorld(glm::vec2 position) const;
		std::vector<std::vector<GridCell>>* GetGrid() const { return m_Grid.get(); }

		void Render() const override;
	private:
		std::shared_ptr<bdnE::Texture2D> m_pTexture;
		std::unique_ptr<std::vector<std::vector<GridCell>>> m_Grid = std::make_unique<std::vector<std::vector<GridCell>>>();
		void GenerateGrid(const std::string& sourceFile);
		void GenerateGridConnections();
		ConnectionType CheckNeighborConnection(CellType current, CellType neighbor) const;
		void SetTextureIds();

		glm::vec2 m_CellSize{ 8.f,8.f };
	};

}


