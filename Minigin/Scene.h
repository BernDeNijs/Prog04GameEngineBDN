#pragma once
#include "SceneManager.h"
//#include "GameObject.h"

namespace bdnE
{
	class GameObject;
	class Scene final
	{
		friend bdnE::Scene* SceneManager::CreateScene(const std::string& name);
	public:

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(GameObject* parent, bool keepWorldPosition);

		void Update() const;
		void FixedUpdate() const;
		void Render() const;
		void RenderImgui() const;
		void DeleteDeadGameObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string GetSceneName() { return m_Name; }

		void SetMarkedForDelete(bool condition) { m_MarkedForDelete = condition; }
		bool GetMarkedForDelete() const { return m_MarkedForDelete; }

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::unique_ptr<GameObject>> m_Objects;

		static unsigned int m_IdCounter; 

		bool m_MarkedForDelete = false;
	};

}
