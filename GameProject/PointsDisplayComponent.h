#pragma once
#include "Observer.h"
#include "GameComponent.h"
#include "TextComponent.h"
#include "PickupComponent.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace dae
{
    class PointsDisplayComponent :public Observer, public GameComponent
    {
    public:
        explicit PointsDisplayComponent(GameObject* owner);

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;


    private:
        void SetScoreDisplay(int itemId);

        std::weak_ptr<TextComponent> m_pTextComponent;

        int m_Score = 0;
    };
}
