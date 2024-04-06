#include "FpsComponent.h"

bdnG::FpsComponent::FpsComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
	if (owner->HasComponent<TextComponent>() == false)
	{
		owner->AddComponent<TextComponent>();
	}

	m_pTextComponent = owner->GetComponent<TextComponent>();
}

void bdnG::FpsComponent::Update()
{
	auto& time = bdnE::GameTime::GetInstance();
	const float deltaT = time.GetDeltaTime();
	
	if (deltaT <= 0.f)
	{
		return;
	}

	m_Timer += deltaT;
	m_count++;

	if (m_Timer >= m_RefreshRate)
	{
		if (const auto sharedPtr = m_pTextComponent.lock()) {
			sharedPtr->SetText(std::format("{:.1f}", m_count / m_Timer));
		}
		m_count = 0;
		m_Timer = 0.f;
	}
}
