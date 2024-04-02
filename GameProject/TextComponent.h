#pragma once
#include "GameComponent.h"
#include "Font.h"
#include <string>
#include "RenderComponent.h"
#include "Texture2D.h"

#include <stdexcept>
#include <SDL_ttf.h>
namespace dae
{
	class TextComponent : public GameComponent
	{
	public:
		explicit TextComponent(GameObject* owner);
		explicit TextComponent(GameObject* owner, const std::string& text);
		explicit TextComponent(GameObject* owner, const std::string& text, int fontSize);
		explicit TextComponent(GameObject* owner, const std::string& text, const std::shared_ptr<dae::Font>& font);

		void Update() override;

		void SetText(const std::string& text);
		void SetText(const std::string& text, int fontSize);
		void SetText(const std::string& text, const std::shared_ptr<dae::Font>& font);

		void SetColor(SDL_Color newColor) { m_Color = newColor; m_needsUpdate = true; }
	private:
		bool m_needsUpdate{ true };
		std::string m_text{ "Lorem Ipsum" };
		std::shared_ptr<dae::Font> m_font{};
		std::shared_ptr<dae::Texture2D> m_textTexture;
		SDL_Color m_Color = { 255,255,255 };
		std::weak_ptr<RenderComponent> m_pRenderer;

	};
}

