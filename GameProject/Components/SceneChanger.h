#pragma once
class SceneChanger
{
};


#pragma once
#include "Observer.h"
#include "GameComponent.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace bdnG
{
    class TextRender;

    class SceneChanger final :public bdnE::Observer, public bdnE::GameComponent
    {
    public:
        explicit SceneChanger(bdnE::GameObject* owner);

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;
        void Render()const override;

    private:
        void LoadEndLevel();
        int m_NrOfPickups = 0;
    };
}
