#include "TextRender.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

bdnG::TextRender::TextRender(bdnE::GameObject* owner) : GameComponent(owner)
{
	m_font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

}

bdnG::TextRender::TextRender(bdnE::GameObject* owner, const std::string& text) : TextRender(owner) 
{ 
	SetText(text); 
}

bdnG::TextRender::TextRender(bdnE::GameObject* owner, const std::string& text, int fontSize) : TextRender(owner)
{
	SetText(text, fontSize);
}

bdnG::TextRender::TextRender(bdnE::GameObject* owner, const std::string& text, const std::shared_ptr<bdnE::Font>& font) : TextRender(owner)
{ 
	SetText(text, font); 
}

void bdnG::TextRender::Update()
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

		bdnE::Renderer::GetInstance().RenderTexture(*m_textTexture, m_pOwner->GetWorldTransform(), false);

	}
}

void bdnG::TextRender::SetText(const std::string& text)
{
	SetText(text, 36);
}

void bdnG::TextRender::SetText(const std::string& text, int fontSize)
{
	const auto font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	SetText(text, font);
}

void bdnG::TextRender::SetText(const std::string& text, const std::shared_ptr<bdnE::Font>& font)
{
	if (text.c_str() == m_text.c_str() && font == m_font) return;
	m_text = text;
	m_font = font;
	m_needsUpdate = true;

}
