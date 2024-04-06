#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameComponent.h"
#include "ranges"


bdnE::GameObject::GameObject(GameObject* parent, bool keepWorldPosition): GameObject()
{
	SetParent(parent, keepWorldPosition);
}



bdnE::GameObject::~GameObject() = default;



//UPDATES
void bdnE::GameObject::Update()
{
	for (const auto& component : m_pComponents| std::views::values) {
		component->Update();
	}
}
void bdnE::GameObject::LateUpdate()
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->LateUpdate();
	}
}
void bdnE::GameObject::FixedUpdate()
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->FixedUpdate();
	}
}
void bdnE::GameObject::Render() const
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->Render();
	}
}

void bdnE::GameObject::RenderImgui() const
{
	for (const auto& component : m_pComponents | std::views::values) {
		component->RenderImGui();
	}
}


//TRANSFORM
void bdnE::GameObject::SetTransformDirty()
{
	m_Transform.IsDirty = true;
	for (const auto& child : m_pChildren)
	{
		child->SetTransformDirty();
	}
}

bdnE::Transform bdnE::GameObject::GetLocalTransform() const
{
	return m_Transform.LocalTransform;
}

bdnE::Transform bdnE::GameObject::GetWorldTransform()
{
	if (m_Transform.IsDirty)
	{
		UpdateWorldTransform();
	}
	return m_Transform.WorldTransform;
}



void bdnE::GameObject::UpdateWorldTransform()
{	
	if (m_pParent != nullptr)
	{
		const auto parentTransform = m_pParent->GetWorldTransform();
		m_Transform.WorldTransform.Position = parentTransform.Position + m_Transform.LocalTransform.Position;
		m_Transform.WorldTransform.Rotation = parentTransform.Rotation + m_Transform.LocalTransform.Rotation;
		m_Transform.WorldTransform.Scale = parentTransform.Scale + m_Transform.LocalTransform.Scale;
		
	}
	else
	{
		m_Transform.WorldTransform.Position = m_Transform.LocalTransform.Position;
		m_Transform.WorldTransform.Rotation = m_Transform.LocalTransform.Rotation;
		m_Transform.WorldTransform.Scale = m_Transform.LocalTransform.Scale;
	}
	m_Transform.IsDirty = false;
}


void bdnE::GameObject::SetLocalTransform(const bdnE::Transform& transform)
{
	m_Transform.LocalTransform = transform;
	SetTransformDirty();
}

void bdnE::GameObject::SetLocalPosition(glm::vec3 position)
{
	//m_LocalPosition = position;
	m_Transform.LocalTransform.Position = position;
	SetTransformDirty();
}

void bdnE::GameObject::SetLocalPosition(glm::vec2 position)
{
	SetLocalPosition({ position.x,position.y,0 });
}

void bdnE::GameObject::SetLocalRotation(glm::vec3 rotation)
{
	m_Transform.LocalTransform.Rotation = rotation;
	SetTransformDirty();
}

void bdnE::GameObject::SetLocalScale(glm::vec3 scale)
{
	m_Transform.LocalTransform.Scale = scale;
	SetTransformDirty();
}

void bdnE::GameObject::SetLocalScale(float scale)
{
	SetLocalScale({ scale,scale,scale });
}


//SCENEGRAPH
void bdnE::GameObject::SetParent(bdnE::GameObject* parent, bool keepWorldPosition)
{
	//Check if new parent is valid
	if (IsChild(parent) || parent == this)
		return;
	if (m_pParent != nullptr)
	{
		if (parent == m_pParent)
		{
			return;
		}
	}
	//UpdatePosition
	if (parent == nullptr)
	{
		if (keepWorldPosition)
		{
			SetLocalTransform(GetWorldTransform());
		}
		else
		{
			SetTransformDirty();
		}
	}		
	else
	{
		if (keepWorldPosition)
		{
			SetLocalTransform(GetLocalTransform() - parent->GetWorldTransform());
		}
		else
		{
			SetTransformDirty();
		}	
	}
	//Remove self from parent
	if (m_pParent != nullptr)
	{
		auto& parentChildren = m_pParent->m_pChildren;
		parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this));

	}
	//Set new parent
	m_pParent = parent;

	//Add self to new parent
	if (m_pParent != nullptr)
	{
		m_pParent->m_pChildren.push_back(this);
	}
}

bool bdnE::GameObject::IsChild(bdnE::GameObject* potentialChild) const
{
	for (const auto& child : m_pChildren)
	{
		if (potentialChild == child or child->IsChild(potentialChild))
		{
			return true;
		}
	}
	return false;
}

