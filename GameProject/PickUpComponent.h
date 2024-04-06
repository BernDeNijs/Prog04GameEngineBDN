#pragma once
#include "GameComponent.h"
#include "Subject.h"

namespace bdnG
{
	class PickUpComponent :public bdnE::GameComponent, public bdnE::Subject
	{
	public:

		explicit PickUpComponent(bdnE::GameObject* owner);
		void PickUpItem(int itemId);

	private:


	};
}