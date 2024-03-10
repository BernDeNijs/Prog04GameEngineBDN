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


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Programming 4 Assignment");

	auto go = scene.CreateGameObject();
	//auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>("background.tga");
	//go->SetTexture("background.tga");
	//scene.Add(go);

	go = scene.CreateGameObject();
	//go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>("logo.tga");
	go->SetLocalPosition({ 216,180 });
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = scene.CreateGameObject();
	//auto to = std::make_shared<dae::GameObject>();
	to->AddComponent<TextComponent>("Programming 4 Assignment", font);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetLocalPosition({ 80, 20 });
	//scene.Add(to);


	const auto emptyObject = scene.CreateGameObject();
	//const auto emptyObject = std::make_shared<dae::GameObject>();
	emptyObject->SetLocalPosition({ 300.f,400.f });
	//scene.Add(emptyObject);

	to = scene.CreateGameObject(to, false);
	//to = std::make_shared<dae::GameObject>(to.get(), false);
	to->AddComponent<RenderComponent>("PacMan.png");
	to->AddComponent<OrbitComponent>(20.f, 2.f);
	//scene.Add(to);
	
	to->SetParent(emptyObject, false); //SetParent Test02

	
	to = scene.CreateGameObject(to, false);
	//to = std::make_shared<dae::GameObject>(to.get(), false);
	to->AddComponent<RenderComponent>("GhostRed.png");
	to->AddComponent<OrbitComponent>(20.f, -1.5f);
	//scene.Add(to);

	to = scene.CreateGameObject();
	//to = std::make_shared<dae::GameObject>();
	to->AddComponent<FpsComponent>();
	//scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}