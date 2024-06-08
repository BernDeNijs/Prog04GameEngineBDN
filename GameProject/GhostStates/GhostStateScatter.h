#pragma once
#include <glm/vec2.hpp>

#include "GhostState.h"
namespace bdnG {
	class PowerPelletComponent;

	class GhostStateScatter : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman) override;
		void Exit() override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent) override;
		void Render(GhostRenderer* renderer) override;
	private:
		float m_ChaseSpeed = 100.f;
		glm::vec2 m_ScatterTarget = { 30,30 };

		float m_Timer = 0;
		float m_MaxTimer = 7.f;
	};
}
