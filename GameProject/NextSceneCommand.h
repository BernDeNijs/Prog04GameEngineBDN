#pragma once
#include "Command.h"

namespace bdnG
{
    class NextSceneCommand final : public bdnE::Command
    {
    public:
        NextSceneCommand() = default;

        void Execute() override {
            auto& instance = bdnE::SceneManager::GetInstance();
            instance.SetActiveScene("NextScene");
            auto& currentScene = instance.GetCurrentScene();
            auto const name = currentScene.GetSceneName();
            instance.RemoveScene(name);
        }
    private:
        
    };
}


