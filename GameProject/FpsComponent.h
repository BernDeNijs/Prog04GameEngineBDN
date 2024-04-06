#pragma once
#include "GameComponent.h"
#include "TextComponent.h"

namespace bdnG
{
	class FpsComponent :public bdnE::GameComponent
	{
	public:

		explicit FpsComponent(bdnE::GameObject* owner);
		void Update() override;

	private:
		float m_RefreshRate = 0.2f;
		float m_Timer{ m_RefreshRate };
		int m_count{ 0 };
		std::weak_ptr<TextComponent> m_pTextComponent;
	};
}
