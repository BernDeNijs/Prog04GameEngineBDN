#pragma once
#include "../GameObject.h"
#include "Command.h"
#include "../Components/MoveComponent.h"


class MoveCommand : public Command {
public:
    MoveCommand(dae::GameObject* gameObject, glm::vec3 direction) : Command(gameObject), m_Direction{direction} {}

    void Execute() override {
        // Check if the GameObject has a MoveComponent
        if (const auto moveComponent = m_GameObject->GetComponent<dae::MoveComponent>().lock()) {
            moveComponent->MoveInDirection(m_Direction);
        }
    }
private:
    glm::vec3 m_Direction{ 0,0,0 };
};

//// Command for moving the GameObject right
//class MoveRightCommand : public Command {
//public:
//    MoveRightCommand(dae::GameObject* gameObject) : Command(gameObject) {}
//
//    void Execute() override {
//        // Check if the GameObject has a MoveComponent
//        if (const auto moveComponent = m_GameObject->GetComponent<dae::MoveComponent>().lock()) {
//            moveComponent->MoveInDirection(glm::vec3{1,0,0});
//        }
//    }
//};
//class MoveLeftCommand : public Command {
//public:
//    MoveLeftCommand(dae::GameObject* gameObject) : Command(gameObject) {}
//
//    void Execute() override {
//        // Check if the GameObject has a MoveComponent
//        if (const auto moveComponent = m_GameObject->GetComponent<dae::MoveComponent>().lock()) {
//            moveComponent->MoveInDirection(glm::vec3{ -1,0,0 });
//        }
//    }
//};
//class MoveUpCommand : public Command {
//public:
//    MoveUpCommand(dae::GameObject* gameObject) : Command(gameObject) {}
//
//    void Execute() override {
//        // Check if the GameObject has a MoveComponent
//        if (const auto moveComponent = m_GameObject->GetComponent<dae::MoveComponent>().lock()) {
//            moveComponent->MoveInDirection(glm::vec3{ 0,-1,0 });
//        }
//    }
//};
//class MoveDownCommand : public Command {
//public:
//    MoveDownCommand(dae::GameObject* gameObject) : Command(gameObject) {}
//
//    void Execute() override {
//        // Check if the GameObject has a MoveComponent
//        if (const auto moveComponent = m_GameObject->GetComponent<dae::MoveComponent>().lock()) {
//            moveComponent->MoveInDirection(glm::vec3{ 0,1,0 });
//        }
//    }
//};
