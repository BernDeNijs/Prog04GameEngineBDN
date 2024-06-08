#pragma once
#include "GameComponent.h"
#include "Subject.h"
#include "Texture2D.h"

namespace bdnG
{
	class CircleCollider;
	enum class ItemType
	{
		pellet,
		bonus,
		powerPellet		
	};

	class PickUp final :public bdnE::GameComponent, public bdnE::Subject,public bdnE::Observer
	{
	public:

		explicit PickUp(bdnE::GameObject* owner, ItemType type);
		void CollidedWithPlayer(CircleCollider* other);
		void Render() const override;

		ItemType GetType() const { return m_Type; }

		virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;
	private:
		ItemType m_Type;
		std::shared_ptr<bdnE::Texture2D> m_pTexture;

	};
}
