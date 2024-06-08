#pragma once
#include "GhostState.h"
namespace bdnG {
	class PowerPelletComponent;

	class GhostStateFrightened : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman) override;
		void Exit() override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent) override;
		void Render(GhostRenderer* renderer) override;
	private:

		float m_Timer = 0;
		float m_MaxTimer = 10.f;
		float m_ChaseSpeed = 10.f;
	};
}
