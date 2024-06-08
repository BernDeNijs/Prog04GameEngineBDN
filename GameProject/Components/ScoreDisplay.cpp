#include "ScoreDisplay.h"
#include "GameObject.h"
#include "PacmanController.h"
#include "PickUp.h"
#include <SDL_ttf.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "TextRender.h"

bdnG::ScoreDisplay::ScoreDisplay(bdnE::GameObject* owner): GameComponent(owner)
{
	for (const auto& object : m_pOwner->GetScene()->GetAllObjectsInScene())
	{
		const auto pickupComponent = object->GetComponent<PickUp>();
		if (pickupComponent == nullptr) return;
		pickupComponent->AddObserver(this);
		m_NrOfPickups++;
	}
	m_pTextRenderer = m_pOwner->AddComponent<TextRender>();


}

void bdnG::ScoreDisplay::OnNotify(const std::string& eventName,
	const std::unordered_map<std::string, std::any>& eventData)
{
	if (eventName == "ItemPickedUp")
	{
		auto iter = eventData.find("itemType");
		bdnG::ItemType itemType = ItemType::pellet;
		if (iter != eventData.end()) {
			itemType = std::any_cast<bdnG::ItemType>(iter->second);
		}

		

		iter = eventData.find("collidingObject");
		bdnE::GameObject* collidingObject = nullptr;
		if (iter != eventData.end()) {
			collidingObject = std::any_cast<bdnE::GameObject*>(iter->second);
		}

		if (collidingObject == nullptr)return;

		if (itemType == ItemType::pellet)
		{
			AddScore(10, collidingObject->GetComponent<PacmanController>()->GetId());
		}
		if (itemType == ItemType::powerPellet)
		{
			AddScore(50, collidingObject->GetComponent<PacmanController>()->GetId());
		}
	}
}

void bdnG::ScoreDisplay::Render() const
{
	


}

void bdnG::ScoreDisplay::AddScore(int amount, int playerId)
{
	if (playerId == 0)
	{
		m_Scores["Player 01"] += amount;
	}
	else
	{
		m_Scores["Player 02"] += amount;
	}

	//generate text to display
	std::string displayText = "";
	for (const auto& score : m_Scores)
	{
		displayText += score.first;
		displayText += " : ";
		displayText += std::to_string(score.second);
		displayText += "\n";

	}

	m_pTextRenderer->SetText(displayText);
}
