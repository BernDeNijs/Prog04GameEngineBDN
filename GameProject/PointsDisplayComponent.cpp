#include "PointsDisplayComponent.h"

dae::PointsDisplayComponent::PointsDisplayComponent(GameObject* owner) : GameComponent(owner)
{
    if (owner->HasComponent<TextComponent>() == false)
    {
        owner->AddComponent<TextComponent>();
    }
    m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void dae::PointsDisplayComponent::OnNotify(const std::string& eventName,
	const std::unordered_map<std::string, std::any>& eventData)
{
    if (eventName == "PickedUpAnItem")
    {
        auto iter = eventData.find("LatestPickup");
        if (iter != eventData.end()) {
            SetScoreDisplay(std::any_cast<int>(iter->second));
        }



    }
}

void dae::PointsDisplayComponent::SetScoreDisplay(int itemId)
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
