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
using namespace dae;
#include "Components/RenderComponent.h"
#include "Components/FpsComponent.h"
#include "Components/OrbitComponent.h"
#include "Components/TTCComponent.h"

#define EXERCISE_SCENEGRAPH
#define EXERCISE_IMGUI

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




}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}