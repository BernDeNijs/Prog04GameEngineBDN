#include "PickUpComponent.h"

dae::PickUpComponent::PickUpComponent(GameObject* owner) : GameComponent(owner)
{
	m_EventData.emplace("LatestPickup", -1); //initialize data with invalid id
}

void dae::PickUpComponent::PickUpItem(int itemId)
{
	m_EventData["LatestPickup"] = itemId;
	Notify("PickedUpAnItem");
}
