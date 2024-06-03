#pragma once
#include "GameComponent.h"


namespace bdnG
{
	class RenderComponent;
	class GhostState;


	class GhostControllerComponent:public bdnE::GameComponent
	{
	public:
		explicit GhostControllerComponent(bdnE::GameObject* owner, bdnE::GameObject* target);

		void Update() override;
		void Render() const override;

	private:
		std::unique_ptr<GhostState> m_CurrentState;
		bdnG::RenderComponent* m_pRenderer { nullptr };
		bdnE::GameObject* m_pTarget{ nullptr };
		//GhostState* m_CurrentState;
	};
}
