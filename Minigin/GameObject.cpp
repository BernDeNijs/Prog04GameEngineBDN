#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameComponent.h"
#include "ranges"


dae::GameObject::GameObject()
{
	//AddComponent<TransformComponent>();
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

