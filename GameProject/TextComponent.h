#pragma once
#include "GameComponent.h"
#include "Font.h"
#include <string>
#include "RenderComponent.h"
#include "Texture2D.h"

#include <stdexcept>
#include <SDL_ttf.h>
namespace bdnG
{
	class TextComponent : public bdnE::GameComponent
	{
	public:
		explicit TextComponent(bdnE::GameObject* owner);
		explicit TextComponent(bdnE::GameObject* owner, const std::string& text);
		explicit TextComponent(bdnE::GameObject* owner, const std::string& text, int fontSize);
		explicit TextComponent(bdnE::GameObject* owner, const std::string& text, const std::shared_ptr<bdnE::Font>& font);

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
		std::weak_ptr<bdnG::RenderComponent> m_pRenderer;

	};
}

