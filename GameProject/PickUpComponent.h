#pragma once
#include "GameComponent.h"
#include "Subject.h"

namespace dae
{
	class PickUpComponent :public GameComponent, public Subject
	{
	public:

		explicit PickUpComponent(GameObject* owner);
		void PickUpItem(int itemId);

	private:


	};
}