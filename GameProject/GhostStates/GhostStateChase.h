#pragma once

#include "GhostState.h"
namespace bdnG {

	class GhostStateChase : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman) override;
		void Exit() override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent) override;
		void Render(GhostRenderer* renderer) override;
	private:
		float m_ChaseSpeed = 100.f;

		float m_Timer = 0;
		float m_MaxTimer = 20.f;
	};
}