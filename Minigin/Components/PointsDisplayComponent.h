#pragma once
#include "../Observers/Observer.h"
#include "GameComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any
#include "../Steam/CSteamAchievements.h"

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
                auto iter = eventData.find("ScoreComponent");
                if (iter != eventData.end()) {
                    SetScoreDisplay(std::any_cast<ScoreComponent*>(iter->second));
                }

               

            }
        }

        void SetSteamAchievements(CSteamAchievements* steamAchievements)
        {
            m_pSteamAchievements = steamAchievements;
        }
    private:
        void SetScoreDisplay(ScoreComponent* scoreComponent) const
        {
            if (const auto textComponent = m_pTextComponent.lock())
            {
                const std::string text = "#Score: " + std::to_string(scoreComponent->GetScore());
                textComponent->SetText(text, 16);
            }
            if (m_pSteamAchievements != nullptr)
            {
                if (scoreComponent->GetScore() >= 500)
                {
                    m_pSteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
                }
            }
            
        }
        std::weak_ptr<TextComponent> m_pTextComponent;
        CSteamAchievements* m_pSteamAchievements;
    };
}
