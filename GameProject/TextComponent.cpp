#include "TextComponent.h"
#include "GameObject.h"

bdnG::TextComponent::TextComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
	m_font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	if (owner->HasComponent<bdnG::RenderComponent>() == false)
	{
		owner->AddComponent<bdnG::RenderComponent>();
	}

	m_pRenderer = owner->GetComponent<bdnG::RenderComponent>();
}

bdnG::TextComponent::TextComponent(bdnE::GameObject* owner, const std::string& text) : TextComponent(owner) 
{ 
	SetText(text); 
}

bdnG::TextComponent::TextComponent(bdnE::GameObject* owner, const std::string& text, int fontSize) : TextComponent(owner)
{
	SetText(text, fontSize);
}

bdnG::TextComponent::TextComponent(bdnE::GameObject* owner, const std::string& text, const std::shared_ptr<bdnE::Font>& font) : TextComponent(owner)
{ 
	SetText(text, font); 
}

void bdnG::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(bdnE::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<bdnE::Texture2D>(texture);

		if (GetOwner() != nullptr)
		{

			if (const auto sharedPtr = m_pRenderer) {
				sharedPtr->SetTexture(m_textTexture);
			}
			m_needsUpdate = false;
		}
	}
}

void bdnG::TextComponent::SetText(const std::string& text)
{
	SetText(text, 36);
}

void bdnG::TextComponent::SetText(const std::string& text, int fontSize)
{
	const auto font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	SetText(text, font);
}

void bdnG::TextComponent::SetText(const std::string& text, const std::shared_ptr<bdnE::Font>& font)
{
	if (text.c_str() == m_text.c_str() && font == m_font) return;
	m_text = text;
	m_font = font;
	m_needsUpdate = true;

}
