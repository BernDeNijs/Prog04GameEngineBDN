#pragma once
#include "../Observers/Observer.h"
#include "GameComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
namespace dae
{
	class TextComponent;
	class RemainingLivesDisplayComponent :public Observer, public GameComponent
	{
	public:
		explicit RemainingLivesDisplayComponent(GameObject* owner) : GameComponent(owner)
		{
			if (owner->HasComponent<TextComponent>() == false)
			{
				owner->AddComponent<TextComponent>();
			}
			m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
		}

		virtual void OnNotify(const std::string& eventName, GameObject* pObject) override
		{
			if (eventName == "PlayerDied")
			{
				SetLivesDisplay(pObject);
			}
		}
	private:
		void SetLivesDisplay(GameObject* pObject) const
		{
			if (const auto healthComponent = pObject->GetComponent<HealthComponent>().lock())
			{
				if (const auto textComponent = m_pTextComponent.lock())
				{
					const std::string text = "Lives: " + std::to_string(healthComponent->GetLives());
					textComponent->SetText(text, 16);
				}
			}
		}
		std::weak_ptr<TextComponent> m_pTextComponent;
	};
}
