#pragma once
#include "GameComponent.h"
namespace dae
{
	class MoveComponent : public dae::GameComponent
	{
	public:
		explicit MoveComponent(GameObject* owner) : GameComponent(owner)
		{
		}
		explicit MoveComponent(GameObject* owner, float speed) : MoveComponent(owner)
		{
			m_Speed = speed;
		}
		void MoveInDirection(glm::vec3 direction) const 
		{
			glm::vec3 position = m_pOwner->GetLocalTransform().Position;
			position += GameTime::GetDeltaTime() * direction * m_Speed;
			m_pOwner->SetLocalPosition(position);
		}
		
	private:
		
		float m_Speed{ 100.f };
	};
	
}


