#pragma once
#include "../GameObject.h"
#include "Command.h"
#include "../Components/PickupComponent.h"
class PickUpCommand : public Command
{
public:
    PickUpCommand(dae::GameObject* gameObject, int itemId) : Command(gameObject), m_ItemId{ itemId } {}

    void Execute() override {
        // Check if the GameObject has a MoveComponent
        if (const auto scoreComponent = m_GameObject->GetComponent<dae::PickupComponent>().lock()) {
            scoreComponent->PickUpItem(m_ItemId);
        }
    }
private:
    int m_ItemId = -1;
};
