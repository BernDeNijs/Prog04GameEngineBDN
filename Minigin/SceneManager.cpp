#include "SceneManager.h"
#include "InputManager.h"
#include <iostream>

#include "Scene.h"

void bdnE::SceneManager::Update() const
{
	m_ActiveScene->Update();
}

void bdnE::SceneManager::FixedUpdate() const
{
	m_ActiveScene->FixedUpdate();
}

void bdnE::SceneManager::Render() const
{
	m_ActiveScene->Render();
}

void bdnE::SceneManager::RenderImgui() const
{
	m_ActiveScene->RenderImgui();
}

void bdnE::SceneManager::DeleteDeadGameObjects() const
{
	m_ActiveScene->DeleteDeadGameObjects();
}

void bdnE::SceneManager::DeleteDeadScenes() 
{
	//make sure to call this after "UpdateCurrentActiveScene"
	//make sure we're not deleting the scene we're now in
	if (!m_ShouldDeleteScenes) return;

	auto& inputManager = InputManager::GetInstance();

	m_Scenes.erase(std::remove_if(m_Scenes.begin(), m_Scenes.end(),
		[&](const std::shared_ptr<Scene>& scene) {
			if (scene->GetMarkedForDelete() && scene->GetSceneName() != m_ActiveScene->GetSceneName())
			{
				inputManager.RemoveSceneInput(scene->GetSceneName());
				return true;
			}
			return false;
		}),
		m_Scenes.end());
	m_ShouldDeleteScenes = false;
}

void bdnE::SceneManager::UpdateCurrentActiveScene()
{
	if (!m_ShouldChangeScene) return;
	
	m_ShouldChangeScene = false; //Even if we fail to switch we don't want to try again

	if (m_NextScene == nullptr)
	{
		std::cout << "Warning! Tried to switch to scene that was a nullptr.\n";
		return;
	}
	if (m_NextScene->GetMarkedForDelete())
	{
		std::cout << "Warning! Tried to switch to scene marked for delete. SceneName: " << m_NextScene->GetSceneName() << "\n";
		return;
	}

	m_ActiveScene = m_NextScene;
	auto& inputManager = InputManager::GetInstance();
	inputManager.SetActiveScene(m_ActiveScene->GetSceneName());
	


}

bdnE::Scene* bdnE::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	if (static_cast<int>(m_Scenes.size()) == 0)
	{
		m_ActiveScene = scene.get();
		auto& inputManager = InputManager::GetInstance();
		inputManager.SetActiveScene(m_ActiveScene->GetSceneName());
	}

	m_Scenes.push_back(scene);
	return scene.get();
}

void bdnE::SceneManager::RemoveScene(const std::string& name)
{
	for (int i = 0; i < static_cast<int>(m_Scenes.size()); i++)
	{
		if (m_Scenes[i]->GetSceneName() == name)
		{
			m_Scenes[i]->SetMarkedForDelete(true);
			m_ShouldDeleteScenes = true;
			return;
		}
	}
}

void bdnE::SceneManager::SetActiveScene(const std::string& name)
{
	for (int i = 0; i < static_cast<int>(m_Scenes.size()); i++)
	{
		if (m_Scenes[i]->GetSceneName() == name)
		{
			m_NextScene = m_Scenes[i].get();
			m_ShouldChangeScene = true;
			return;
		}
	}
	std::cout << "Could not find scene:" << name << "\n";
}
