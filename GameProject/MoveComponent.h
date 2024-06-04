#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/detail/type_vec2.hpp>

#include "Command.h"
#include "GameComponent.h"

namespace bdnG
{
	class MoveComponent final : public bdnE::GameComponent
	{
	public:
		explicit MoveComponent(bdnE::GameObject* owner);
		explicit MoveComponent(bdnE::GameObject* owner, float speed);
		void MoveInDirection(glm::vec2 direction) const;

	private:
		float m_Speed{ 100.f };

	};

}


