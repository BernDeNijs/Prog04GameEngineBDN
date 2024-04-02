#pragma once
#include "GameComponent.h"
namespace dae
{
	class MoveComponent : public dae::GameComponent
	{
	public:
		explicit MoveComponent(GameObject* owner);
		explicit MoveComponent(GameObject* owner, float speed);
		void MoveInDirection(glm::vec3 direction) const;

	private:
		float m_Speed{ 100.f };

	};

}


