#pragma once
#include "GameComponent.h"
#include "Grid.h"

namespace bdnG
{
	class PickupSpawner final : public bdnE::GameComponent
	{
	public:
		explicit PickupSpawner(bdnE::GameObject* owner, bdnG::Grid* mapObject);
		void Update()override;
	private:
		void SpawnPickups(bdnG::Grid* mapObject);
		void SpawnBonus();

		bdnG::Grid* m_Grid = nullptr;
	};
}

