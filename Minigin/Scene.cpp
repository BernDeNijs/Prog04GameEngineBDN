#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update() const
{
	for(const auto& object : m_objects)
	{
		object->Update();
	}
	for (const auto& object : m_objects)
	{
		object->LateUpdate();
	}
}
void Scene::FixedUpdate()
{
	for(auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::DeleteDeadGameObjects()
{
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		[](const std::shared_ptr<GameObject>& obj) {
			return obj->GetDeathFlag();
		}),
		m_objects.end());
	//for (int i = m_objects.size(); i >= 0 ; i--)
	//{
	//	if (m_objects[i]->GetDeathFlag())
	//	{
	//		m_objects.erase(m_objects.begin() + i);
	//	}
	//}

}

