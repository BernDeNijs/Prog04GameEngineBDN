#pragma once
#include "Observer.h"
#include "GameComponent.h"
#include "TextComponent.h"
#include "Components/PickUp.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace bdnG
{
    class PointsDisplayComponent final :public bdnE::Observer, public bdnE::GameComponent
    {
    public:
        explicit PointsDisplayComponent(bdnE::GameObject* owner);

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;


    private:
        void SetScoreDisplay(int itemId);

        TextComponent* m_pTextComponent;

        int m_Score = 0;
    };
}
