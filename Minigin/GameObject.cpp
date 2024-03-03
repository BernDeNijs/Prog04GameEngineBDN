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
void dae::GameObject::SetTransformDirty()
{
	//m_PositionDirty = true;
	m_Transform.IsDirty = true;
	for (const auto& child : m_pChildren)
	{
		child->SetTransformDirty();
	}
}

dae::Transform dae::GameObject::GetLocalTransform() const
{
	//return m_LocalPosition;
	return m_Transform.LocalTransform;
}

dae::Transform dae::GameObject::GetWorldTransform()
{
	if (m_Transform.IsDirty)
	{
		UpdateWorldTransform();
	}
	//return m_WorldPosition;
	return m_Transform.WorldTransform;
}



void dae::GameObject::UpdateWorldTransform()
{	
	if (const auto sharedPtr = m_pParent.lock())
	{
		//m_WorldPosition = sharedPtr->GetWorldPosition() + m_LocalPosition;
		const auto parentTransform = sharedPtr->GetWorldTransform();
		m_Transform.WorldTransform.Position = parentTransform.Position + m_Transform.LocalTransform.Position;
		m_Transform.WorldTransform.Rotation = parentTransform.Rotation + m_Transform.LocalTransform.Rotation;
		m_Transform.WorldTransform.Scale = parentTransform.Scale + m_Transform.LocalTransform.Scale;
		
	}
	else
	{
		//m_WorldPosition = m_LocalPosition;
		m_Transform.WorldTransform.Position = m_Transform.LocalTransform.Position;
		m_Transform.WorldTransform.Rotation = m_Transform.LocalTransform.Rotation;
		m_Transform.WorldTransform.Scale = m_Transform.LocalTransform.Scale;
	}
	m_Transform.IsDirty = false;
}


void dae::GameObject::SetLocalTransform(const dae::Transform& transform)
{
	m_Transform.LocalTransform = transform;
	SetTransformDirty();
}

void dae::GameObject::SetLocalPosition(glm::vec3 position)
{
	//m_LocalPosition = position;
	m_Transform.LocalTransform.Position = position;
	SetTransformDirty();
}

void dae::GameObject::SetLocalPosition(glm::vec2 position)
{
	SetLocalPosition({ position.x,position.y,0 });
}

void dae::GameObject::SetLocalRotation(glm::vec3 rotation)
{
	m_Transform.LocalTransform.Rotation = rotation;
	SetTransformDirty();
}

void dae::GameObject::SetLocalScale(glm::vec3 scale)
{
	m_Transform.LocalTransform.Scale = scale;
	SetTransformDirty();
}

void dae::GameObject::SetLocalScale(float scale)
{
	SetLocalScale({ scale,scale,scale });
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
	if (const auto sharedPtr = m_pParent.lock())
	{
		//sharedPtr->RemoveChild(this);
		auto& parentChildren = sharedPtr->m_pChildren;
		/*parentChildren.erase(std::remove_if(parentChildren.begin(), parentChildren.end(),
			[this](const std::shared_ptr<GameObject>& ptr) { return ptr.get() == this; }),
			parentChildren.end());*/
		parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this));

	}
	//Set new parent
	m_pParent = parent;

	//Add self to new parent
	if (const auto sharedPtr = m_pParent.lock())
	{
		sharedPtr->m_pChildren.push_back(this);
		//sharedPtr->AddChild(this);
	}
}

bool dae::GameObject::IsChild(const std::shared_ptr<dae::GameObject>& potentialChild) const
{
	for (const auto& child : m_pChildren)
	{
		if (potentialChild.get() == child or child->IsChild(potentialChild))
		{
			return true;
		}
	}
	return false;
}

