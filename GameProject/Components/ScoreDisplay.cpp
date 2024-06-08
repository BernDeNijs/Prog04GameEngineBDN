#include "ScoreDisplay.h"
#include "GameObject.h"
#include "../CharacterControllers/PacmanController.h"
#include "PickUp.h"
#include <SDL_ttf.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "TextRender.h"

#include "../GhostStates/GhostStateChase.h"
#include "../GhostStates/GhostStateDead.h"
#include "../GhostStates/GhostStateFrightened.h"
#include "../GhostStates/GhostStateScatter.h"

bdnG::ScoreDisplay::ScoreDisplay(bdnE::GameObject* owner): GameComponent(owner)
{
	std::vector<bdnE::GameObject*> sceneObjects = m_pOwner->GetScene()->GetAllObjectsInScene();


	for (const auto& object : sceneObjects)
	{
		const auto pacmanController = object->GetComponent<PacmanController>();
		if (pacmanController != nullptr)
		{
			pacmanController->AddObserver(this);
		}


		const auto pickupComponent = object->GetComponent<PickUp>();
		if (pickupComponent == nullptr) continue;
		pickupComponent->AddObserver(this);
		m_NrOfPickups++;

		

	}
	m_pTextRenderer = m_pOwner->AddComponent<TextRender>();
	AddScore(0, 0);

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
		if (itemType == ItemType::bonus)
		{
			AddScore(300, collidingObject->GetComponent<PacmanController>()->GetId());
		}
	}

	if (eventName == "PlayerHitByGhost")
	{
		auto iter = eventData.find("GhostState");
		if (iter != eventData.end()) {

			const auto ghostState = std::any_cast<GhostState*>(iter->second);

			if (dynamic_cast<GhostStateFrightened*>(ghostState) != nullptr) {
				AddScore(200, 0);
				//std::cout << "Ghost is in Chase state.\n";
			}

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
