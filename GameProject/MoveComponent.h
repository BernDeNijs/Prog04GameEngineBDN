#pragma once
#include <glm/vec3.hpp>
#include "GameComponent.h"

namespace bdnG
{
	class MoveComponent final : public bdnE::GameComponent
	{
	public:
		explicit MoveComponent(bdnE::GameObject* owner);
		explicit MoveComponent(bdnE::GameObject* owner, float speed);
		void MoveInDirection(glm::vec3 direction) const;

	private:
		float m_Speed{ 100.f };

	};

}


