#pragma once
#include <map>

#include "GameComponent.h"
#include "Subject.h"

namespace bdnG
{

	class CircleCollider final :public bdnE::GameComponent, public bdnE::Subject
	{
	public:

		explicit CircleCollider(bdnE::GameObject* owner, float radius, const std::string& layer , const std::vector<std::string>& collisionLayers );
		explicit CircleCollider(bdnE::GameObject* owner, float radius, const std::string& layer);
		void AddCollisionLayer(const std::string& layer);
		void RemoveCollisionLayer(const std::string& layer);

		std::string GetLayer() { return m_Layer; };

		void Update()override;
	private:

		inline static std::map<std::string ,std::vector<CircleCollider*>> m_CollisionObjects = {};
		std::vector<std::string> m_CollisionLayers = {};
		float m_Radius = 0;
		void HandleCollision();
		float GetWorldRadius();
		std::string m_Layer;
	};
}