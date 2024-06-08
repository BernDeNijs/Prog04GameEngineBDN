#pragma once
#include <glm/vec2.hpp>

#include "GhostState.h"
namespace bdnG {
	class PickUp;
	class PowerPelletComponent;

	class GhostStateScatter : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman, std::vector< PickUp*>) override;
		void Exit(std::vector< PickUp*>) override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent) override;
		void Render(GhostRenderer* renderer) override;
		void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;
	private:
		float m_ChaseSpeed = 100.f;
		glm::vec2 m_ScatterTarget = { 30,30 };

		float m_Timer = 0;
		float m_MaxTimer = 7.f;

		bool m_PelletActivated = false;
	};
}
