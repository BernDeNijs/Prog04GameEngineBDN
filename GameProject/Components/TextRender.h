#pragma once
#include "GameComponent.h"
#include "Font.h"
#include <string>
#include "Texture2D.h"

#include <stdexcept>
#include <SDL_ttf.h>
namespace bdnG
{
	class TextRender final : public bdnE::GameComponent
	{
	public:
		explicit TextRender(bdnE::GameObject* owner);
		explicit TextRender(bdnE::GameObject* owner, const std::string& text);
		explicit TextRender(bdnE::GameObject* owner, const std::string& text, int fontSize);
		explicit TextRender(bdnE::GameObject* owner, const std::string& text, const std::shared_ptr<bdnE::Font>& font);

		void Update() override;

		void SetText(const std::string& text);
		void SetText(const std::string& text, int fontSize);
		void SetText(const std::string& text, const std::shared_ptr<bdnE::Font>& font);

		void SetColor(SDL_Color newColor) { m_Color = newColor; m_needsUpdate = true; }
	private:
		bool m_needsUpdate{ true };
		std::string m_text{ "Lorem Ipsum" };
		std::shared_ptr<bdnE::Font> m_font{};
		std::shared_ptr<bdnE::Texture2D> m_textTexture;
		SDL_Color m_Color = { 255,255,255 };
	};
}

