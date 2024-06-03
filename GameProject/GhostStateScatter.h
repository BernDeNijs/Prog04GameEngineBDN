#pragma once
#include <glm/vec3.hpp>

#include "GhostState.h"
namespace bdnG {
	class PowerPelletComponent;

	class GhostStateScatter : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman) override;
		void Exit() override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman) override;
		void Render(RenderComponent* renderer) override;
	private:
		float m_ChaseSpeed = 10.f;
		glm::vec3 m_ScatterTarget = { 50,50,0 };
		PowerPelletComponent* m_PelletComp =  nullptr ;

		float m_Timer = 0;
		float m_MaxTimer = 7.f;
	};
}


