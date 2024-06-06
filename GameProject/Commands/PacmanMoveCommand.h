#pragma once
#include "../Components/PacmanMovementComponent.h"
#include "GameObject.h"
#include "Command.h"
namespace bdnG
{
    class PacmanMoveCommand final : public bdnE::Command
    {
    public:
        PacmanMoveCommand(bdnE::GameObject* gameObject, MoveDirections direction) : m_Direction{ direction } 
        {            
            m_MoveComponent = gameObject->GetComponent<PacmanMovementComponent>();
        }

        void Execute() override {
            if (m_MoveComponent != nullptr)
            {
                m_MoveComponent->SetMoveDirection(m_Direction);
            }
        }
    private:
        MoveDirections m_Direction = MoveDirections::none;
        PacmanMovementComponent* m_MoveComponent = nullptr;
    };
}
