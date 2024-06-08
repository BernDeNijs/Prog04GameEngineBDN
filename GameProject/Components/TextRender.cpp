#include "TextRender.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

bdnG::TextRender::TextRender(bdnE::GameObject* owner) : GameComponent(owner)
{
	m_font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

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
		//Clear textures
		m_textTexture = std::vector<std::shared_ptr<bdnE::Texture2D>>();

		for (const auto& text : m_text)
		{

			const auto surf = TTF_RenderText_Blended(m_font->GetFont(), text.c_str(), m_Color);
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
			m_textTexture.push_back( std::make_shared<bdnE::Texture2D>(texture));
		}

		
	}
}

void bdnG::TextRender::Render() const
{
	bdnE::Transform textureTransform = m_pOwner->GetWorldTransform();

	for (const auto& texture : m_textTexture)
	{
		bdnE::Renderer::GetInstance().RenderTexture(*texture, textureTransform);
		
		int width = 0;
		int height = 0;
		SDL_QueryTexture(texture->GetSDLTexture(), nullptr, nullptr, &width, &height);
		textureTransform.Position.y +=  static_cast<float>(height);
	}
	
}

void bdnG::TextRender::SetText(const std::string& text)
{
	SetText(text, 21);
}

void bdnG::TextRender::SetText(const std::string& text, int fontSize)
{
	const auto font = bdnE::ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	SetText(text, font);
}

void bdnG::TextRender::SetText(const std::string& text, const std::shared_ptr<bdnE::Font>& font)
{
	//if (text.c_str() == m_text.c_str() && font == m_font) return;
	m_text = SplitString(text,'\n');
	m_font = font;
	m_needsUpdate = true;

}

std::vector<std::string> bdnG::TextRender::SplitString(const std::string& str, char delimiter) const
{
	std::vector<std::string> lines;
	std::stringstream ss(str);
	std::string line;
	while (std::getline(ss, line, delimiter)) {
		lines.push_back(line);
	}
	return lines;
}
