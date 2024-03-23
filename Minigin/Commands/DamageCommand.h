#pragma once
#include "../GameObject.h"
#include "Command.h"
#include "../Components/HealthComponent.h"
class DamageCommand : public Command
{
public:
    DamageCommand(dae::GameObject* gameObject, int damage) : Command(gameObject), m_Damage{ damage } {}

    void Execute() override {
        // Check if the GameObject has a MoveComponent
        if (const auto healthComponent = m_GameObject->GetComponent<dae::HealthComponent>().lock()) {
            healthComponent->Damage(m_Damage);
        }
    }
private:
    int m_Damage = 1;
};

