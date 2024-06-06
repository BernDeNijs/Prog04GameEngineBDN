#pragma once
#include <glm/vec2.hpp>
#include "GameComponent.h"
#include "GridComponent.h"

namespace bdnG
{
	class PacmanMovementComponent final : public bdnE::GameComponent
	{
	public:
		explicit PacmanMovementComponent(bdnE::GameObject* owner, GridComponent* mapObject, float speed = 100.f);
		void MoveInDirection(glm::vec2 direction) const;
		void SpawnPacmanOnSpawnPoint();

	private:
		float m_Speed{ 100.f };
		GridComponent* m_pGridComponent = nullptr;
		
	};

}

