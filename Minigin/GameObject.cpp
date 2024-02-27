#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components/GameComponent.h"
#include "ranges"


dae::GameObject::GameObject()
{
	//m_pTransform = std::make_shared<Transform>(std::weak_ptr<GameObject>());
	//m_pComponents.emplace(typeid(Transform), m_pTransform);
}

dae::GameObject::GameObject(const std::shared_ptr<GameObject>& parent, bool keepWorldPosition): GameObject()
{
	SetParent(parent, keepWorldPosition);
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
void dae::GameObject::SetPositionDirty()
{
	m_PositionDirty = true;
	for (const auto& child : m_pChildren)
	{
		child->SetPositionDirty();
	}
}

glm::vec3 dae::GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (const auto sharedPtr = m_pParent.lock())
	{
		m_WorldPosition = sharedPtr->GetWorldPosition() + m_LocalPosition;
		return;
	}
	m_WorldPosition = m_LocalPosition;
}

void dae::GameObject::SetLocalPosition(glm::vec3 position)
{
	m_LocalPosition = position;
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(glm::vec2 position)
{
	SetLocalPosition({ position.x,position.y,0 });
}

//SCENEGRAPH
void dae::GameObject::SetParent(const std::shared_ptr<dae::GameObject>& parent, bool keepWorldPosition)
{
	//Check if new parent is valid
	if (IsChild(parent) || parent.get() == this)
		return;
	if (const auto sharedPtr = m_pParent.lock())
	{
		if (parent.get() == sharedPtr.get())
		{
			return;
		}
	}
	//UpdatePosition
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	//Remove self from parent
	if (const auto sharedPtr = m_pParent.lock())
	{
		//sharedPtr->RemoveChild(this);
		auto& parentChildren = sharedPtr->m_pChildren;
		parentChildren.erase(std::remove_if(parentChildren.begin(), parentChildren.end(),
			[this](const std::shared_ptr<GameObject>& ptr) { return ptr.get() == this; }),
			parentChildren.end());

	}
	//Set new parent
	m_pParent = parent;

	//Add self to new parent
	if (const auto sharedPtr = m_pParent.lock())
	{
		sharedPtr->m_pChildren.push_back(std::shared_ptr<GameObject>(this));
		//sharedPtr->AddChild(this);
	}
}

bool dae::GameObject::IsChild(std::shared_ptr<dae::GameObject> potentialChild) const
{
	for (const auto& child : m_pChildren)
	{
		if (potentialChild.get() == child.get() or child->IsChild(potentialChild))
		{
			return true;
		}
	}
	return false;
}

