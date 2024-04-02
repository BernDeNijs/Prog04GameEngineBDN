#pragma once
#include "GameComponent.h"
#include "../Observers/Subject.h"

namespace dae
{
	class PickupComponent :public GameComponent, public Subject
	{
	public:

		explicit PickupComponent(GameObject* owner) : GameComponent(owner)
		{
			m_EventData.emplace("LatestPickup", -1); //initialize data with invalid id
		}
		void PickUpItem(int itemId)
		{
			m_EventData["LatestPickup"] =  itemId;
			Notify("PickedUpAnItem");
		}

	private:


	};
}