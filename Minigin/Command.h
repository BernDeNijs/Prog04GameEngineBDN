#pragma once

#include "GameObject.h"
namespace bdnE
{
    class Command {
    public:
        Command() = default;
        virtual ~Command() = default;
        virtual void Execute() = 0;

    protected:

    };

    class GameObjectCommand : public Command
    {
    public:
        GameObjectCommand(bdnE::GameObject* gameObject) :Command()
        { m_GameObject= gameObject ; }

    protected:
        bdnE::GameObject* m_GameObject;
    };

}


