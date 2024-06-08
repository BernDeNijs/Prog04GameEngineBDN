#pragma once
#include "GameComponent.h"

class PacmanController
{
};
namespace bdnG
{
	class PacmanController final : public bdnE::GameComponent
	{
	public:
		explicit PacmanController(bdnE::GameObject* owner, int id);
		int GetId() { return m_Id; }

	private:
		void BindKeyboardControls();
		void BindControllerControls();
		const int m_Id;
	};

}
