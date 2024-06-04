#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace bdnE
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		bdnE::Scene* CreateScene(const std::string& name);
		void RemoveScene(const std::string& name);

		void SetActiveScene(const std::string& name);

		void Update() const;
		void FixedUpdate() const;
		void Render() const;
		void RenderImgui() const;
		void DeleteDeadGameObjects() const;
		void DeleteDeadScenes();
		void UpdateCurrentActiveScene();

		bdnE::Scene& GetCurrentScene() const { return *m_ActiveScene; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene = nullptr;
		//SceneChanging
		Scene* m_NextScene = nullptr;
		bool m_ShouldChangeScene = false;
		bool m_ShouldDeleteScenes = false;
	};
}
