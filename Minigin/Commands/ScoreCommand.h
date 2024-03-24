#pragma once
#include "../GameObject.h"
#include "Command.h"
#include "../Components/ScoreComponent.h"
class ScoreCommand : public Command
{
public:
    ScoreCommand(dae::GameObject* gameObject, int amount) : Command(gameObject), m_Amount{ amount } {}

    void Execute() override {
        // Check if the GameObject has a MoveComponent
        if (const auto scoreComponent = m_GameObject->GetComponent<dae::ScoreComponent>().lock()) {
            scoreComponent->GainScore(m_Amount);
        }
    }
private:
    int m_Amount = 1;
};
