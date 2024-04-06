#pragma once
#include "Observer.h"
#include "GameComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include <unordered_map> // For using std::unordered_map
#include <any> // For using std::any

namespace bdnG
{
    class RemainingLivesDisplayComponent :public bdnE::Observer, public bdnE::GameComponent
    {
    public:
        explicit RemainingLivesDisplayComponent(bdnE::GameObject* owner);

        virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;

    private:
        void SetLivesDisplay(HealthComponent* healthComponent) const;

        std::weak_ptr<TextComponent> m_pTextComponent;
    };
}