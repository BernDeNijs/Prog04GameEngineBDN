#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update() const
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::FixedUpdate() const
{
	for(auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderImgui() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->RenderImgui();
	}
}

void dae::SceneManager::DeleteDeadGameObjects() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->DeleteDeadGameObjects();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
