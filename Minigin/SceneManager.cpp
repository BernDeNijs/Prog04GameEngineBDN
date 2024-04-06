#include "SceneManager.h"
#include "Scene.h"

void bdnE::SceneManager::Update() const
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void bdnE::SceneManager::FixedUpdate() const
{
	for(auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void bdnE::SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void bdnE::SceneManager::RenderImgui() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->RenderImgui();
	}
}

void bdnE::SceneManager::DeleteDeadGameObjects() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->DeleteDeadGameObjects();
	}
}

bdnE::Scene& bdnE::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
