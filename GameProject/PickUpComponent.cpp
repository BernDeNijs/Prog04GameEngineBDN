#include "PickUpComponent.h"

bdnG::PickUpComponent::PickUpComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
	m_EventData.emplace("LatestPickup", -1); //initialize data with invalid id
}

void bdnG::PickUpComponent::PickUpItem(int itemId)
{
	m_EventData["LatestPickup"] = itemId;
	Notify("PickedUpAnItem");
}
