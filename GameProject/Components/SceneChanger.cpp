#include "SceneChanger.h"

#include <iostream>

#include "GameObject.h"
#include "../CharacterControllers/PacmanController.h"
#include "PickUp.h"
#include <SDL_ttf.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "TextRender.h"

bdnG::SceneChanger::SceneChanger(bdnE::GameObject* owner) : GameComponent(owner)
{
	std::vector<bdnE::GameObject*> sceneObjects = m_pOwner->GetScene()->GetAllObjectsInScene();


	for (const auto& object : sceneObjects)
	{
		const auto pickupComponent = object->GetComponent<PickUp>();
		if (pickupComponent != nullptr)
		{
			if (pickupComponent->GetType() != ItemType::pellet) continue;
			pickupComponent->AddObserver(this);
			m_NrOfPickups++;
		}
		const auto pacmanController = object->GetComponent<PacmanController>();
		if (pacmanController != nullptr)
		{
			pacmanController->AddObserver(this);
		}
	}
}

void bdnG::SceneChanger::OnNotify(const std::string& eventName,
	const std::unordered_map<std::string, std::any>& /*eventData*/)
{	if (eventName == "ItemPickedUp")
	{
		m_NrOfPickups--;
		std::cout << "Pickups remaining: " << m_NrOfPickups << "\n";
		if (m_NrOfPickups <= 0)
		{
			LoadEndLevel();
		}		
	}
	if (eventName == "PlayerHitByGhost")
	{
		LoadEndLevel();
	}
}

void bdnG::SceneChanger::Render() const
{



}

void bdnG::SceneChanger::LoadEndLevel()
{
	auto& sceneManager = bdnE::SceneManager::GetInstance();
	sceneManager.SetActiveScene("GameOver");
}
