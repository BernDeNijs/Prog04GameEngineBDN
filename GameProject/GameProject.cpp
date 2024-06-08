#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif





#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

//GameObject
#include "GameObject.h"

//Components
#include "Components/Grid.h"



//Commands


//Sound
#include "SoundLocator.h"
#include "SDLSoundService.h"
#include "Commands/PacmanMoveCommand.h"
#include "Components/CircleCollider.h"
#include "Components/PacmanController.h"
#include "Components/PacmanMovement.h"
#include "Components/PacmanRender.h"
#include "Components/PickupSpawner.h"
#include "Components/ScoreDisplay.h"


void load()
{
	
	//BASIC SCENE//
	{
		const auto level01 = bdnE::SceneManager::GetInstance().CreateScene("Level01");
		const auto background = level01->CreateGameObject();
		auto gameMap = background->AddComponent<bdnG::Grid>("Level01.txt","GridTiles.png");
		background->SetLocalScale(2.f);
		background->SetLocalPosition({ 0,0,-1 });
		background->SetLocalPosition({ 0,50,-1 });

		const auto pacMan = level01->CreateGameObject();
		pacMan->AddComponent<bdnG::PacmanRender>("PacMan.png");
		pacMan->AddComponent<bdnG::CircleCollider>(5.f, "Pacman");
		pacMan->AddComponent<bdnG::PacmanMovement>(gameMap);
		pacMan->SetLocalScale(2.f);
		pacMan->AddComponent<bdnG::PacmanController>(0);

		const auto pickupSpawner = level01->CreateGameObject();
		pickupSpawner->AddComponent<bdnG::PickupSpawner>(gameMap);

		const auto pointsDisplay = level01->CreateGameObject();
		pointsDisplay->AddComponent<bdnG::ScoreDisplay>();
		pointsDisplay->SetLocalPosition({ 0.f, 0.f, 1.f });

	}

	{
		//GLOBAL STUFF//
		//auto global = bdnE::SceneManager::GetInstance().GetGlobalScene();
		//auto pacMan = global->CreateGameObject();
		//pacMan->AddComponent<bdnG::PacmanRenderComponent>("PacMan.png");
	}

}



int main(int, char* []) {

	bdnE::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}