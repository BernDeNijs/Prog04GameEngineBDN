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
#include "DamageCommand.h"
#include "PickUpCommand.h"
#include "HealthComponent.h"
#include "PointsDisplayComponent.h"
#include "RemainingLivesDisplayComponent.h"
#include "PickupComponent.h"
//Components
using namespace dae;
#include "RenderComponent.h"
#include "FpsComponent.h"
#include "OrbitComponent.h"
#include "TTCComponent.h"
#include "MoveComponent.h"

#include "MoveCommands.h"

//#define EXERCISE_SCENEGRAPH
//#define EXERCISE_IMGUI
//#define EXERCISE_COMMAND
#define EXERCISE_OBSERVER


void load()
{
	//BASIC SCENE//
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Programming 4 Assignment");

	auto go = scene.CreateGameObject();
	go->AddComponent<RenderComponent>("background.tga");


	go = scene.CreateGameObject();
	go->AddComponent<RenderComponent>("logo.tga");
	go->SetLocalPosition({ 216,180 });

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = scene.CreateGameObject();
	to->AddComponent<TextComponent>("Programming 4 Assignment", font);
	to->SetLocalPosition({ 80, 20 });

	const auto fpsObject = scene.CreateGameObject();
	fpsObject->AddComponent<FpsComponent>();
	//---

#ifdef EXERCISE_SCENEGRAPH
	const auto emptyObject = scene.CreateGameObject();
	emptyObject->SetLocalPosition({ 300.f,400.f });

	to = scene.CreateGameObject(to, false);
	to->AddComponent<RenderComponent>("PacMan.png");
	to->AddComponent<OrbitComponent>(20.f, 2.f);

	to->SetParent(emptyObject, false); //SetParent Test02


	to = scene.CreateGameObject(to, false);
	to->AddComponent<RenderComponent>("GhostRed.png");
	to->AddComponent<OrbitComponent>(20.f, -1.5f);
#endif // Exercise_SceneGraph

#ifdef EXERCISE_IMGUI
	const auto trashTheCacheObject = scene.CreateGameObject();
	trashTheCacheObject->AddComponent<TTCComponent>();

#endif // DEBUG
#ifdef EXERCISE_COMMAND
	auto controllableCharacter = scene.CreateGameObject();
	controllableCharacter->AddComponent<RenderComponent>("PacMan.png");
	controllableCharacter->AddComponent<MoveComponent>();

	const Controller* controller = InputManager::AddController();
	controller->AddButtonBinding(ControllerButton::DPadRight, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ 1,0,0 }));
	controller->AddButtonBinding(ControllerButton::DPadLeft, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ -1,0,0 }));
	controller->AddButtonBinding(ControllerButton::DPadUp, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ 0,-1,0 }));
	controller->AddButtonBinding(ControllerButton::DPadDown, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ 0,1,0 }));

	controllableCharacter = scene.CreateGameObject();
	controllableCharacter->AddComponent<RenderComponent>("GhostRed.png");
	controllableCharacter->AddComponent<MoveComponent>(200.f);

	auto keyboard = InputManager::GetKeyboardController();
	keyboard->AddButtonBinding(SDL_SCANCODE_W, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ 0,-1,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_S, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ 0,1,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_A, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ -1,0,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_D, KeyState::pressed, std::make_shared<MoveCommand>(controllableCharacter, glm::vec3{ 1,0,0 }));


	//Control explaination
	auto textObject = scene.CreateGameObject();
	textObject->AddComponent<TextComponent>("Move pacman with the D-Pad", font);
	textObject->SetLocalPosition({ 10,400 });
	textObject = scene.CreateGameObject();
	textObject->AddComponent<TextComponent>("Move the ghost with WASD", font);
	textObject->SetLocalPosition({ 10,450 });
#endif // EXERCISE_COMMAND

#ifdef EXERCISE_OBSERVER

	//PLAYER ONE
	//--Character
	auto playerCharacter = scene.CreateGameObject();
	playerCharacter->AddComponent<RenderComponent>("PacMan.png");
	playerCharacter->AddComponent<MoveComponent>();
	auto healthComponent = playerCharacter->AddComponent<HealthComponent>();
	auto scoreComponent = playerCharacter->AddComponent<PickUpComponent>();

	//--Lives display
	auto DisplayObject = scene.CreateGameObject();
	auto text = DisplayObject->AddComponent<TextComponent>();
	text->SetText("Lives: 3", 16);
	DisplayObject->SetLocalPosition({ 10,300 });
	auto livesDisplay = DisplayObject->AddComponent<RemainingLivesDisplayComponent>();
	healthComponent->AddObserver(livesDisplay.get());

	//--Score display
	DisplayObject = scene.CreateGameObject();
	text = DisplayObject->AddComponent<TextComponent>();
	text->SetText("#Score: 3", 16);
	DisplayObject->SetLocalPosition({ 10,315 });
	auto pointDisplay = DisplayObject->AddComponent<PointsDisplayComponent>();
	scoreComponent->AddObserver(pointDisplay.get());


	//--Add controls
	const Controller* controller = InputManager::AddController();
	controller->AddButtonBinding(ControllerButton::DPadRight, KeyState::pressed, std::make_shared<MoveCommand>(playerCharacter, glm::vec3{ 1,0,0 }));
	controller->AddButtonBinding(ControllerButton::DPadLeft, KeyState::pressed, std::make_shared<MoveCommand>(playerCharacter, glm::vec3{ -1,0,0 }));
	controller->AddButtonBinding(ControllerButton::DPadUp, KeyState::pressed, std::make_shared<MoveCommand>(playerCharacter, glm::vec3{ 0,-1,0 }));
	controller->AddButtonBinding(ControllerButton::DPadDown, KeyState::pressed, std::make_shared<MoveCommand>(playerCharacter, glm::vec3{ 0,1,0 }));

	controller->AddButtonBinding(ControllerButton::ButtonA, KeyState::releasedThisFrame, std::make_shared<DamageCommand>(playerCharacter, 1));
	controller->AddButtonBinding(ControllerButton::ButtonB, KeyState::releasedThisFrame, std::make_shared<PickUpCommand>(playerCharacter, 0));
	controller->AddButtonBinding(ControllerButton::ButtonY, KeyState::releasedThisFrame, std::make_shared<PickUpCommand>(playerCharacter, 1));





	//ENEMY CHARACTER
	//--Character
	auto enemyCharacter = scene.CreateGameObject();
	enemyCharacter->AddComponent<RenderComponent>("GhostRed.png");
	enemyCharacter->AddComponent<MoveComponent>(200.f);
	healthComponent = enemyCharacter->AddComponent<HealthComponent>();
	scoreComponent = enemyCharacter->AddComponent<PickUpComponent>();

	//--Lives display
	DisplayObject = scene.CreateGameObject();
	text = DisplayObject->AddComponent<TextComponent>();
	text->SetText("Lives: 3", 16);
	DisplayObject->SetLocalPosition({ 10,330 });
	livesDisplay = DisplayObject->AddComponent<RemainingLivesDisplayComponent>();
	healthComponent->AddObserver(livesDisplay.get());

	//--Score display
	DisplayObject = scene.CreateGameObject();
	text = DisplayObject->AddComponent<TextComponent>();
	text->SetText("#Score: 3", 16);
	DisplayObject->SetLocalPosition({ 10,345 });
	pointDisplay = DisplayObject->AddComponent<PointsDisplayComponent>();
	scoreComponent->AddObserver(pointDisplay.get());

	//--Add controls
	auto keyboard = InputManager::GetKeyboardController();
	keyboard->AddButtonBinding(SDL_SCANCODE_W, KeyState::pressed, std::make_shared<MoveCommand>(enemyCharacter, glm::vec3{ 0,-1,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_S, KeyState::pressed, std::make_shared<MoveCommand>(enemyCharacter, glm::vec3{ 0,1,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_A, KeyState::pressed, std::make_shared<MoveCommand>(enemyCharacter, glm::vec3{ -1,0,0 }));
	keyboard->AddButtonBinding(SDL_SCANCODE_D, KeyState::pressed, std::make_shared<MoveCommand>(enemyCharacter, glm::vec3{ 1,0,0 }));

	keyboard->AddButtonBinding(SDL_SCANCODE_C, KeyState::releasedThisFrame, std::make_shared<DamageCommand>(enemyCharacter, 1));
	keyboard->AddButtonBinding(SDL_SCANCODE_Z, KeyState::releasedThisFrame, std::make_shared<PickUpCommand>(enemyCharacter, 0));
	keyboard->AddButtonBinding(SDL_SCANCODE_X, KeyState::releasedThisFrame, std::make_shared<PickUpCommand>(enemyCharacter, 1));



	//CONTROLS EXPLAINATION
	auto textObject = scene.CreateGameObject();
	textObject->AddComponent<TextComponent>("Move pacman with the D-Pad, Hurt pacman with A , Gain points with B & Y", 16);
	textObject->SetLocalPosition({ 10,400 });
	textObject = scene.CreateGameObject();
	textObject->AddComponent<TextComponent>("Move the ghost with WASD, Hurt ghost with C , Gain points with Z & X", 16);
	textObject->SetLocalPosition({ 10,420 });
	textObject = scene.CreateGameObject();

#endif // EXERCISE_OBSERVER



}



int main(int, char* []) {

	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}