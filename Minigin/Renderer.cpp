#include <stdexcept>
#include "Renderer.h"

#include "GameObject.h"
#include "imgui.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void bdnE::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void bdnE::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().RenderImgui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void bdnE::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void bdnE::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, bool centered) const
{
	Transform newTransform = Transform();
	newTransform.Position = { x,y };
	RenderTexture(texture, newTransform, centered);
}

void bdnE::Renderer::RenderTexture(const Texture2D& texture, const Transform& transform, bool centered) const
{
	RenderTexture(texture, transform, nullptr, centered);
}

void bdnE::Renderer::RenderTexture(const Texture2D& texture, const Transform& transform, const SDL_Rect* srcRect, bool centered) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(transform.Position.x);
	dst.y = static_cast<int>(transform.Position.y);


	if (srcRect == nullptr)
	{
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	}
	else
	{
		dst.w = srcRect->w;
		dst.h = srcRect->h;
	}
	dst.w *= static_cast<int>(transform.Scale.x);
	dst.h *= static_cast<int>(transform.Scale.y);

	const auto rot = static_cast<double>(transform.Rotation);
	const auto center = SDL_Point(static_cast<int>(static_cast<float>(dst.w) * 0.5f), static_cast<int>(static_cast<float>(dst.h) * 0.5f));

	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	if (dst.w < 0)
	{
		dst.w *= -1;
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
	}

	if (centered)
	{
		dst.x -= center.x;
		dst.y -= center.y;
	}

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), srcRect, &dst, rot, &center, flip);
}

SDL_Renderer* bdnE::Renderer::GetSDLRenderer() const { return m_renderer; }
