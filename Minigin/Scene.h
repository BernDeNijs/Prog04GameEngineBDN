#pragma once
#include "SceneManager.h"
#include "GameObject.h"
namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		//void Add(std::shared_ptr<GameObject> object);
		GameObject* CreateGameObject();
		GameObject* CreateGameObject(GameObject* parent, bool keepWorldPosition);
		//void Remove(std::shared_ptr<GameObject> object);
		//void RemoveAll();

		void Update() const;
		void FixedUpdate();
		void Render() const;
		void DeleteDeadGameObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_Objects{};
		//std::vector < std::unique_ptr<GameObject>> m_Objects{};

		static unsigned int m_idCounter; 
	};

}
