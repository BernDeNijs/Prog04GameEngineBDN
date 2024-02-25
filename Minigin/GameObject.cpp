#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components/GameComponent.h"
#include "ranges"
#include "Components/TransformComponent.h"


dae::GameObject::GameObject()
{
	m_pTransform = AddComponent<TransformComponent>();
	//m_pTransform = std::make_shared<TransformComponent>(std::weak_ptr<GameObject>());
	//m_pComponents.emplace(typeid(TransformComponent), m_pTransform);
}



dae::GameObject::~GameObject() = default;



void dae::GameObject::Update()
{
	for (const auto& component : m_pComponents| std::views::values) {
		component->Update();
	}
}
void dae::GameObject::LateUpdate()
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->LateUpdate();
	}
}
void dae::GameObject::FixedUpdate()
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->FixedUpdate();
	}
}
void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->Render();
	}
}


//POSITION
void dae::GameObject::SetTransform(glm::vec2 position) const
{
	m_pTransform->SetTransform(position);
}

void dae::GameObject::SetTransform(glm::vec3 position) const
{
	m_pTransform->SetTransform(position);
}


