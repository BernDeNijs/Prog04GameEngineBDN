#include "RemainingLivesDisplayComponent.h"
#include "GameObject.h"

bdnG::RemainingLivesDisplayComponent::RemainingLivesDisplayComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
    if (owner->HasComponent<TextComponent>() == false)
    {
        owner->AddComponent<TextComponent>();
    }
    m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void bdnG::RemainingLivesDisplayComponent::OnNotify(const std::string& eventName,
	const std::unordered_map<std::string, std::any>& eventData)
{
    if (eventName == "PlayerDied")
    {
        auto iter = eventData.find("HealthComponent");
        if (iter != eventData.end()) {
            SetLivesDisplay(std::any_cast<HealthComponent*>(iter->second));
        }
    }
}

void bdnG::RemainingLivesDisplayComponent::SetLivesDisplay(HealthComponent* healthComponent) const
{
    if (const auto textComponent = m_pTextComponent)
    {
        const std::string text = "Lives: " + std::to_string(healthComponent->GetLives());
        textComponent->SetText(text, 16);
    }
}
