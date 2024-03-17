#include <SDL.h>
#include "InputManager.h"

#include <SDL_syswm.h>
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	//ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	//XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...


	}
	//Update controllers
	for (const auto& pController : m_pControllers)
	{
		pController->HandleInputs();
	}
	m_Keyboard->HandleInputs();
	return true;
}

Controller* dae::InputManager::AddController()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	m_pControllers.push_back(std::make_unique<Controller>(index));

	return m_pControllers.back().get();
}
