#pragma once
#include "../Observers/Observer.h"
#include "GameComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace dae
{
    class RemainingLivesDisplayComponent :public Observer, public GameComponent
    {
    public:
        explicit RemainingLivesDisplayComponent(GameObject* owner) : GameComponent(owner)
        {
            if (owner->HasComponent<TextComponent>() == false)
            {
                owner->AddComponent<TextComponent>();
            }
            m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
        }

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override
        {
            if (eventName == "PlayerDied")
            {
                auto iter = eventData.find("HealthComponent");
                if (iter != eventData.end()) {
                    SetLivesDisplay(std::any_cast<HealthComponent*>(iter->second));
                }
            }
        }
    private:
        void SetLivesDisplay(HealthComponent* healthComponent) const
        {
            if (const auto textComponent = m_pTextComponent.lock())
            {
                const std::string text = "Lives: " + std::to_string(healthComponent->GetLives());
                textComponent->SetText(text, 16);
            }
        }
        std::weak_ptr<TextComponent> m_pTextComponent;
    };
}