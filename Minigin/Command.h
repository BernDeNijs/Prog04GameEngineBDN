#pragma once

#include "GameObject.h"
namespace bdnE
{
    class Command {
    public:
        Command(bdnE::GameObject* gameObject) : m_GameObject{ gameObject } {}
        virtual ~Command() {}
        virtual void Execute() = 0;

    protected:
        bdnE::GameObject* m_GameObject;
    };
}


