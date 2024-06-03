#pragma once

#include "GhostState.h"
namespace bdnG {
	class PowerPelletComponent;

	class GhostStateChase : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman) override;
		void Exit() override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman) override;
		void Render(RenderComponent* renderer) override;
	private:
		float m_ChaseSpeed = 10.f;
		PowerPelletComponent* m_PelletComp = nullptr;

		float m_Timer = 0;
		float m_MaxTimer = 20.f;
	};
}