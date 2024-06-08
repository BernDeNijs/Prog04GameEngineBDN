
#pragma once
#include "Observer.h"
#include "GameComponent.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace bdnG
{
    class TextRender;

    class ScoreDisplay final :public bdnE::Observer, public bdnE::GameComponent
    {
    public:
        explicit ScoreDisplay(bdnE::GameObject* owner);

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;
        void Render()const override;

    private:
        void AddScore(int amount, int playerId);
        int m_NrOfPickups = 0;
        std::unordered_map<std::string, int> m_Scores {};
        TextRender* m_pTextRenderer = nullptr;
    };
}
