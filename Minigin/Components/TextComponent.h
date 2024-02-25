#pragma once
#include "GameComponent.h"
#include "../Font.h"
#include <string>
#include "RenderComponent.h"
#include "../Texture2D.h"

#include <stdexcept>
#include <SDL_ttf.h>
namespace dae
{
	class TextComponent : public GameComponent
	{
	public:
		explicit TextComponent(GameObject* owner) : GameComponent(owner) { m_font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);}
		explicit TextComponent(GameObject* owner, const std::string& text) : GameComponent(owner) { SetText(text); }
		explicit TextComponent(GameObject* owner, const std::string& text, const std::shared_ptr<dae::Font>& font) : GameComponent(owner) { SetText(text, font); }


		void Update() override
		{
			if (m_needsUpdate)
			{
				const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
				if (surf == nullptr)
				{
					throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
				}
				auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
				if (texture == nullptr)
				{
					throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
				}
				SDL_FreeSurface(surf);
				m_textTexture = std::make_shared<dae::Texture2D>(texture);

				if (m_pOwner != nullptr)
				{
					m_pOwner->GetComponent<RenderComponent>()->SetTexture(m_textTexture);
					m_needsUpdate = false;
				}
			}
		}
		void LateUpdate() override {}
		void FixedUpdate() override {}
		void Render() const override
		{
		}
		void RenderImGui() override {}
		void SetText(const std::string& text)
		{
			const auto font =  dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			SetText(text, font);
		}
		void SetText(const std::string& text, const std::shared_ptr<dae::Font>& font)
		{
			m_text = text;
			m_font = font;
			m_needsUpdate = true;
			if (m_pOwner != nullptr)
			{
				if (m_pOwner->HasComponent<RenderComponent>() == false)
				{
					m_pOwner->AddComponent<RenderComponent>();
				}
			}
		}
		void SetColor(SDL_Color newColor) { m_Color = newColor; m_needsUpdate = true; }
	private:
		bool m_needsUpdate{true};
		std::string m_text;
		std::shared_ptr<dae::Font> m_font;
		std::shared_ptr<dae::Texture2D> m_textTexture;
		SDL_Color m_Color = { 255,255,255 };

	};
}

