#pragma once
#include <glm/vec3.hpp>

#include "GhostState.h"
namespace bdnG {
	class PowerPelletComponent;

	class GhostStateDead : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman) override;
		void Exit() override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman) override;
		void Render(RenderComponent* renderer) override;
	private:
		glm::vec3 m_HousePos{ 200.f,200.f,0 };
		float m_ChaseSpeed = 10.f;
	};
}