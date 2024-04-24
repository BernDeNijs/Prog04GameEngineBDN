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
#include "InputManager.h"

//GameObject
#include "GameObject.h"

//Components
#include "RenderComponent.h"
#include "FpsComponent.h"
#include "MoveComponent.h"
#include "HealthComponent.h"
#include "PointsDisplayComponent.h"
#include "RemainingLivesDisplayComponent.h"
#include "PickupComponent.h"

//Commands
#include "DamageCommand.h"
#include "PickUpCommand.h"
#include "MoveCommands.h"


void load()
{
	//INPUT MANAGER//
	auto& inputManager = bdnE::InputManager::GetInstance();

	//BASIC SCENE//
	auto& scene = bdnE::SceneManager::GetInstance().CreateScene("Programming 4 Assignment");
	auto go = scene.CreateGameObject();
	go->AddComponent<bdnG::RenderComponent>("background.tga");

	go = scene.CreateGameObject();
	go->AddComponent<bdnG::RenderComponent>("logo.tga");
	go->SetLocalPosition({ 216,180 });

	auto font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = scene.CreateGameObject();
	to->AddComponent<bdnG::TextComponent>("Programming 4 Assignment", font);
	to->SetLocalPosition({ 80, 20 });

	//auto test = bdnE::GameObject();
	//auto test = std::make_unique<bdnE::GameObject>();

	const auto fpsObject = scene.CreateGameObject();
	fpsObject->AddComponent<bdnG::FpsComponent>();
	//---



	//PLAYER ONE
	//--Character
	auto playerCharacter = scene.CreateGameObject();
	playerCharacter->AddComponent<bdnG::RenderComponent>("PacMan.png");
	playerCharacter->AddComponent<bdnG::MoveComponent>();
	auto healthComponent = playerCharacter->AddComponent<bdnG::HealthComponent>();
	auto scoreComponent = playerCharacter->AddComponent<bdnG::PickUpComponent>();

	//--Lives display
	auto DisplayObject = scene.CreateGameObject();
	auto text = DisplayObject->AddComponent<bdnG::TextComponent>();
	text->SetText("Lives: 3", 16);
	DisplayObject->SetLocalPosition({ 10,300 });
	auto livesDisplay = DisplayObject->AddComponent<bdnG::RemainingLivesDisplayComponent>();
	healthComponent->AddObserver(livesDisplay);

	//--Score display
	DisplayObject = scene.CreateGameObject();
	text = DisplayObject->AddComponent<bdnG::TextComponent>();
	text->SetText("#Score: 3", 16);
	DisplayObject->SetLocalPosition({ 10,315 });
	auto pointDisplay = DisplayObject->AddComponent<bdnG::PointsDisplayComponent>();
	scoreComponent->AddObserver(pointDisplay);


	//--Add controls
	const bdnE::Controller* controller = inputManager.AddController();
	controller->AddButtonBinding(bdnE::ControllerButton::DPadRight, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(playerCharacter, glm::vec3{ 1,0,0 }));
	controller->AddButtonBinding(bdnE::ControllerButton::DPadLeft, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(playerCharacter, glm::vec3{ -1,0,0 }));
	controller->AddButtonBinding(bdnE::ControllerButton::DPadUp, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(playerCharacter, glm::vec3{ 0,-1,0 }));
	controller->AddButtonBinding(bdnE::ControllerButton::DPadDown, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(playerCharacter, glm::vec3{ 0,1,0 }));

	controller->AddButtonBinding(bdnE::ControllerButton::ButtonA, bdnE::KeyState::releasedThisFrame, std::make_shared<bdnG::DamageCommand>(playerCharacter, 1));
	controller->AddButtonBinding(bdnE::ControllerButton::ButtonB, bdnE::KeyState::releasedThisFrame, std::make_shared<bdnG::PickUpCommand>(playerCharacter, 0));
	controller->AddButtonBinding(bdnE::ControllerButton::ButtonY, bdnE::KeyState::releasedThisFrame, std::make_shared<bdnG::PickUpCommand>(playerCharacter, 1));





	//ENEMY CHARACTER
	//--Character
	auto enemyCharacter = scene.CreateGameObject();
	enemyCharacter->AddComponent<bdnG::RenderComponent>("GhostRed.png");
	enemyCharacter->AddComponent<bdnG::MoveComponent>(200.f);
	healthComponent = enemyCharacter->AddComponent<bdnG::HealthComponent>();
	scoreComponent = enemyCharacter->AddComponent<bdnG::PickUpComponent>();

	//--Lives display
	DisplayObject = scene.CreateGameObject();
	text = DisplayObject->AddComponent<bdnG::TextComponent>();
	text->SetText("Lives: 3", 16);
	DisplayObject->SetLocalPosition({ 10,330 });
	livesDisplay = DisplayObject->AddComponent<bdnG::RemainingLivesDisplayComponent>();
	healthComponent->AddObserver(livesDisplay);

	//--Score display
	DisplayObject = scene.CreateGameObject();
	text = DisplayObject->AddComponent<bdnG::TextComponent>();
	text->SetText("#Score: 3", 16);
	DisplayObject->SetLocalPosition({ 10,345 });
	pointDisplay = DisplayObject->AddComponent<bdnG::PointsDisplayComponent>();
	scoreComponent->AddObserver(pointDisplay);

	//--Add controls
	auto keyboard = inputManager.GetKeyboardController();
	keyboard->AddButtonBinding(SDL_SCANCODE_W, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(enemyCharacter, glm::vec3{ 0,-1,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_S, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(enemyCharacter, glm::vec3{ 0,1,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_A, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(enemyCharacter, glm::vec3{ -1,0,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_D, bdnE::KeyState::pressed, std::make_shared<bdnG::MoveCommand>(enemyCharacter, glm::vec3{ 1,0,0 }));

	keyboard->AddButtonBinding(SDL_SCANCODE_C, bdnE::KeyState::releasedThisFrame, std::make_shared<bdnG::DamageCommand>(enemyCharacter, 1));
	keyboard->AddButtonBinding(SDL_SCANCODE_Z, bdnE::KeyState::releasedThisFrame, std::make_shared<bdnG::PickUpCommand>(enemyCharacter, 0));
	keyboard->AddButtonBinding(SDL_SCANCODE_X, bdnE::KeyState::releasedThisFrame, std::make_shared<bdnG::PickUpCommand>(enemyCharacter, 1));



	//CONTROLS EXPLAINATION
	auto textObject = scene.CreateGameObject();
	textObject->AddComponent<bdnG::TextComponent>("Move pacman with the D-Pad, Hurt pacman with A , Gain points with B & Y", 16);
	textObject->SetLocalPosition({ 10,400 });
	textObject = scene.CreateGameObject();
	textObject->AddComponent<bdnG::TextComponent>("Move the ghost with WASD, Hurt ghost with C , Gain points with Z & X", 16);
	textObject->SetLocalPosition({ 10,420 });
	textObject = scene.CreateGameObject();



}



int main(int, char* []) {

	bdnE::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}