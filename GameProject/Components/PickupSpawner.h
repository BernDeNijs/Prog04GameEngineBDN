#pragma once
#include "GameComponent.h"
#include "GridComponent.h"

namespace bdnG
{
	class PickupSpawner final : public bdnE::GameComponent
	{
	public:
		explicit PickupSpawner(bdnE::GameObject* owner, bdnG::GridComponent* mapObject);
	private:
		void SpawnPickups(bdnG::GridComponent* mapObject);
	};
}

