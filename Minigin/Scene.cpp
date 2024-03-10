#include "Scene.h"
//#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

//void Scene::Add(std::shared_ptr<GameObject> object)
//{
//	m_Objects.emplace_back(std::move(object));
//}

GameObject* Scene::CreateGameObject()
{
	m_Objects.emplace_back(std::make_unique<GameObject>());
	return m_Objects.back().get();
}

GameObject* Scene::CreateGameObject(GameObject* parent, bool keepWorldPosition)
{
	m_Objects.emplace_back(std::make_unique<GameObject>(parent, keepWorldPosition));
	return m_Objects.back().get();
}

//void Scene::Remove(std::shared_ptr<GameObject> object)
//{
//	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
//}

//void Scene::RemoveAll()
//{
//	m_objects.clear();
//}

void Scene::Update() const
{
	for(const auto& object : m_Objects)
	{
		object->Update();
	}
	for (const auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}
void Scene::FixedUpdate()
{
	for(auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::DeleteDeadGameObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return obj->GetDeathFlag();
		}),
		m_Objects.end());
	//for (int i = m_objects.size(); i >= 0 ; i--)
	//{
	//	if (m_objects[i]->GetDeathFlag())
	//	{
	//		m_objects.erase(m_objects.begin() + i);
	//	}
	//}

}

