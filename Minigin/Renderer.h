#pragma once
#include <SDL.h>
#include "Singleton.h"

namespace bdnE
{
	struct Transform;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */

	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, bool centered = false) const;
		void RenderTexture(const Texture2D& texture, const Transform& transform, bool centered = false) const;
		void RenderTexture(const Texture2D& texture, const Transform& transform, const SDL_Rect* srcRect, bool centered = false) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	private:
		
	};
}

