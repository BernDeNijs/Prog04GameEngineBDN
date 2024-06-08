#pragma once
#include "GameObject.h"
#include "Command.h"
#include "Components/PickUp.h"
#include "PowerPelletComponent.h"

namespace bdnG
{
    class PickUpCommand final : public bdnE::GameObjectCommand
    {
    public:
        PickUpCommand(bdnE::GameObject* gameObject, int itemId) : GameObjectCommand(gameObject), m_ItemId{ itemId } {}

        void Execute() override {
            // Check if the GameObject has a MoveComponent
            if (m_ItemId == 2)
            {
                m_GameObject->GetComponent<PowerPelletComponent>()->PickUpPellet();
                return;
            }

            if (const auto scoreComponent = m_GameObject->GetComponent<bdnG::PickUp>()) {
                scoreComponent->PickUpItem(m_ItemId);
            }
        }
    private:
        int m_ItemId = -1;
    };


}

