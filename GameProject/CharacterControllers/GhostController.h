#pragma once
#include "GameComponent.h"


namespace bdnG
{
	class PickUp;
	class PacmanMovement;
	class GhostRenderer;
	class GhostState;


	class GhostController :public bdnE::GameComponent
	{
	public:
		explicit GhostController(bdnE::GameObject* owner, bdnE::GameObject* target );

		void Update() override;
		void Render() const override;
		GhostState* GetState() const { return m_CurrentState.get(); }


	private:
		std::unique_ptr<GhostState> m_CurrentState;
		bdnG::GhostRenderer* m_pRenderer{ nullptr };
		bdnE::GameObject* m_pTarget{ nullptr };
		bdnG::PacmanMovement* m_MovementComponent;
		std::vector< PickUp*> m_PowerPellets{};
	};
}