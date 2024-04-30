#pragma once
#include "GameObject.h"
#include "Command.h"

#include "HealthComponent.h"
namespace bdnG
{
    class DamageCommand final : public bdnE::GameObjectCommand
    {
    public:
        DamageCommand(bdnE::GameObject* gameObject, int damage) : GameObjectCommand(gameObject), m_Damage{ damage } {}

        void Execute() override {
            // Check if the GameObject has a MoveComponent
            if (const auto healthComponent = m_GameObject->GetComponent<bdnG::HealthComponent>()) {
                healthComponent->Damage(m_Damage);
            }
        }
    private:
        int m_Damage = 1;
    };
}


