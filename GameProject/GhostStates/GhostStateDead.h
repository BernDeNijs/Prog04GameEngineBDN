#pragma once
#include <glm/vec2.hpp>

#include "GhostState.h"
namespace bdnG {
	class PickUp;
	class PowerPelletComponent;

	class GhostStateDead : public GhostState
	{
	public:
		void Enter(bdnE::GameObject* pacman, std::vector< PickUp*>) override;
		void Exit(std::vector< PickUp*>) override;
		GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent) override;
		void Render(GhostRenderer* renderer) override;
		void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;
	private:
		glm::vec2 m_HousePos{ 200.f,200.f };
		float m_ChaseSpeed = 10.f;
	};
}