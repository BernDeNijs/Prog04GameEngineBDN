#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace bdnE;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

GameObject* Scene::CreateGameObject()
{
	std::unique_ptr<GameObject> object{ new GameObject() };
	m_Objects.emplace_back(std::move(object));
	return m_Objects.back().get();
	//m_TestObject.emplace_back(new GameObject());
	//return m_TestObject[0];
	//m_Objects.emplace_back(std::make_unique<GameObject>());
	//return m_Objects.back().get();
}

GameObject* Scene::CreateGameObject(GameObject* parent, bool keepWorldPosition)
{
	std::unique_ptr<GameObject> object{ new GameObject() };
	m_Objects.emplace_back(std::move(object));
	m_Objects.back()->SetParent(parent, keepWorldPosition);
	return m_Objects.back().get();
	//m_Objects.emplace_back(std::make_unique<GameObject>(parent, keepWorldPosition));
	//return m_Objects.back().get();
}

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
void Scene::FixedUpdate() const
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

void Scene::RenderImgui() const
{
	for (const auto& object : m_Objects)
	{
		object->RenderImgui();
	}
}

void Scene::DeleteDeadGameObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return obj->GetDeathFlag();
		}),
		m_Objects.end());

}

