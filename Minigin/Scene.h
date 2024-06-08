#pragma once
#include "SceneManager.h"
//#include "GameComponent.h"
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


		//template<typename T>
		//std::vector<T*> GetAllComponentsOfType()
		//{
		//	static_assert(std::is_base_of_v<GameComponent, T>, "Cannot get component that does not inherit from GameComponent");

		//	std::vector<T*> foundObjects{};
		//	for (const auto& object : m_Objects)
		//	{
		//		T* component = object.get()->GetComponent<T>();
		//		if (component != nullptr)
		//		{
		//			foundObjects.push_back(component);
		//		}
		//	}

		//	return foundObjects;
		//}

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::unique_ptr<GameObject>> m_Objects;

		static unsigned int m_IdCounter; 

		bool m_MarkedForDelete = false;
	};

}
