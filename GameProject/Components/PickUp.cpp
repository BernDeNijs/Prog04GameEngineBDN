#include "PickUp.h"

#include <iostream>

#include "CircleCollider.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

bdnG::PickUp::PickUp(bdnE::GameObject* owner , ItemType type) : GameComponent(owner)
{
	auto collider = m_pOwner->AddComponent<CircleCollider>(2.f,"Pickup");
	collider->AddCollisionLayer("Pacman");
	collider->AddObserver(this);

	m_Type = type;


	m_EventData.emplace("LatestPickup", -1); //initialize data with invalid id
	m_pTexture = bdnE::ResourceManager::GetInstance().LoadTexture("GridTiles.png");
}



void bdnG::PickUp::OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData)
{

	if (eventName == "CollisionStay")
	{
		auto iter = eventData.find("other");
		if (iter != eventData.end()) {
			CollidedWithPlayer(std::any_cast<CircleCollider*>(iter->second));
		}
	}


}
void bdnG::PickUp::CollidedWithPlayer(CircleCollider* other)
{
	m_EventData["itemType"] = m_Type;
	m_EventData["collidingObject"] = other->GetOwner();
	Notify("ItemPickedUp");
	m_pOwner->SetDeathFlag();

	//For debug purposes:
	std::cout << "Item Picked up of type " << static_cast<int>(m_Type) << "\n";


}

void bdnG::PickUp::Render() const
{
    const auto& renderer = bdnE::Renderer::GetInstance();
    const bdnE::Transform pointTransform = m_pOwner->GetWorldTransform();
	constexpr int cellSize = 8;
	const int textureId = 45 + static_cast<int>(m_Type);
    SDL_Rect srcRect;
    srcRect.x = (textureId % 16) * static_cast<int>(cellSize + 1);
    srcRect.y = (textureId / 16) * static_cast<int>(cellSize + 1);
    srcRect.w = static_cast<int>(cellSize);
    srcRect.h = static_cast<int>(cellSize);

    renderer.RenderTexture(*m_pTexture, pointTransform, &srcRect,true);

}
