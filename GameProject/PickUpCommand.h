#pragma once
#include "GameObject.h"
#include "Command.h"
#include "PickUpComponent.h"
namespace bdnG
{
    class PickUpCommand final : public bdnE::GameObjectCommand
    {
    public:
        PickUpCommand(bdnE::GameObject* gameObject, int itemId) : GameObjectCommand(gameObject), m_ItemId{ itemId } {}

        void Execute() override {
            // Check if the GameObject has a MoveComponent
            if (const auto scoreComponent = m_GameObject->GetComponent<bdnG::PickUpComponent>()) {
                scoreComponent->PickUpItem(m_ItemId);
            }
        }
    private:
        int m_ItemId = -1;
    };
}

