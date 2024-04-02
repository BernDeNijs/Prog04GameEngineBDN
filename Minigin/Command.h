#pragma once

#include "GameObject.h"

class Command {
public:
    Command(dae::GameObject* gameObject) : m_GameObject{ gameObject } {}
    virtual ~Command() {}
    virtual void Execute() = 0;

protected:
    dae::GameObject* m_GameObject;
};

