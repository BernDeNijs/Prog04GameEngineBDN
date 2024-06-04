#include <SDL.h>
#include "InputManager.h"

#include <SDL_syswm.h>
#include <backends/imgui_impl_sdl2.h>

bool bdnE::InputManager::ProcessInput() const
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
	for (int i = 0; i < static_cast<int>(m_pControllers.size()); i++)
	{
		m_pControllers[i]->HandleInputs();
		for (const auto& binding : m_ActionBindings[i])
		{
			m_pControllers[i]->CheckBinding(binding);
		}
	}
	for (const auto& pController : m_pControllers)
	{
		pController->HandleInputs();
	}
	//Handle keyboard events
	m_Keyboard->HandleInputs();
	for(const auto& binding : m_KeyBinds)
	{
		m_Keyboard->CheckBinding(binding);
	}
	return true;
}

int bdnE::InputManager::AddController()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	m_pControllers.push_back(std::make_unique<Controller>(index));
	m_ActionBindings.push_back(std::vector<ControllerBinding>{});
	return index;
}

void bdnE::InputManager::AddButtonBinding(ControllerButton button, KeyState keyState,
                                          std::shared_ptr<bdnE::Command> command, int controllerIdx) 
{
	AddButtonBinding(ControllerBinding{ button ,keyState,std::move(command)}, controllerIdx);
}

void bdnE::InputManager::AddButtonBinding(const ControllerBinding& keyBind, int controllerIdx) 
{
	m_ActionBindings[controllerIdx].emplace_back(keyBind);
}

void bdnE::InputManager::AddKeyboardBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command)
{
	AddKeyboardBinding({ button,keyState,command });
}

void bdnE::InputManager::AddKeyboardBinding(const KeyboardBinding& keyBind)
{
	m_KeyBinds.emplace_back(keyBind);
}
