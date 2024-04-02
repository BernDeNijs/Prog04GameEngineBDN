#pragma once
#include "../Observers/Observer.h"
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
        explicit PointsDisplayComponent(GameObject* owner) : GameComponent(owner)
        {
            if (owner->HasComponent<TextComponent>() == false)
            {
                owner->AddComponent<TextComponent>();
            }
            m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
        }

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override
        {
            if (eventName == "PickedUpAnItem")
            {
                auto iter = eventData.find("LatestPickup");
                if (iter != eventData.end()) {
                    SetScoreDisplay(std::any_cast<int>(iter->second));
                }

               

            }
        }

    private:
        void SetScoreDisplay(int itemId) 
        {

            if (itemId == 0)
            {
                m_Score += 50;
            }
            if (itemId == 1)
            {
                m_Score += 100;
            }


            if (const auto textComponent = m_pTextComponent.lock())
            {
                const std::string text = "#Score: " + std::to_string(m_Score);
                textComponent->SetText(text, 16);
            }
            
        }
        std::weak_ptr<TextComponent> m_pTextComponent;

        int m_Score = 0;
    };
}
