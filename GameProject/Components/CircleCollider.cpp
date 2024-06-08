#include "CircleCollider.h"

#include <glm/detail/func_geometric.inl>


#include "GameObject.h"

bdnG::CircleCollider::CircleCollider(bdnE::GameObject* owner, float radius, const std::string& layer,
                                     const std::vector<std::string>& collisionLayers):CircleCollider(owner,radius,layer)
{
	m_CollisionLayers = collisionLayers;
}

bdnG::CircleCollider::CircleCollider(bdnE::GameObject* owner, float radius, const std::string& layer) :GameComponent(owner)
{
	m_CollisionObjects[layer].push_back(this);
	m_Radius = radius;

	m_EventData["Collider"] = this;
}

void bdnG::CircleCollider::AddCollisionLayer(const std::string& layer)
{
	m_CollisionLayers.push_back(layer);
}

void bdnG::CircleCollider::RemoveCollisionLayer(const std::string& layer)
{
	m_CollisionLayers.erase(
		std::remove(m_CollisionLayers.begin(), m_CollisionLayers.end(), layer),
		m_CollisionLayers.end()
	);
}

void bdnG::CircleCollider::Update()
{
	HandleCollision();
}

void bdnG::CircleCollider::HandleCollision()
{
	const glm::vec2 position = m_pOwner->GetWorldTransform().Position;
	const float radius = GetWorldRadius();

	for (const auto& layer : m_CollisionLayers)
	{
		for (const auto& collider : m_CollisionObjects[layer])
		{
			if (collider == this) continue;
			const float distance = glm::length(collider->m_pOwner->GetWorldTransform().Position - position);
			const float touchDistance = collider->GetWorldRadius() + radius;
			if (distance <= touchDistance)
			{
				m_EventData["other"] = collider;
				Notify("CollisionStay");
			}
		}
	}
}

float bdnG::CircleCollider::GetWorldRadius()
{
	const auto scale = m_pOwner->GetWorldTransform().Scale;
	return m_Radius * (std::max(scale.x, scale.y));
}


