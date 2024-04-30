#pragma once
#include "GameObject.h"
#include "Command.h"
#include "MoveComponent.h"

namespace bdnG
{
    class MoveCommand final : public bdnE::GameObjectCommand {
    public:
        MoveCommand(bdnE::GameObject* gameObject, glm::vec3 direction) : GameObjectCommand(gameObject), m_Direction{ direction } {}

        void Execute() override {
            // Check if the GameObject has a MoveComponent
            if (const auto moveComponent = m_GameObject->GetComponent<bdnG::MoveComponent>()) {
                moveComponent->MoveInDirection(m_Direction);
            }
        }
    private:
        glm::vec3 m_Direction{ 0,0,0 };
    };
}

