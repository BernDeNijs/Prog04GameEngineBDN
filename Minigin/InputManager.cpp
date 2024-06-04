#include <SDL.h>
#include "InputManager.h"

#include <SDL_syswm.h>
#include <backends/imgui_impl_sdl2.h>
#include "Scene.h"

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
			if (binding.second != m_SceneName)
			{
				continue;
			}
			m_pControllers[i]->CheckBinding(binding.first);
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
		if (binding.second != m_SceneName)
		{
			continue;
		}
		m_Keyboard->CheckBinding(binding.first);
	}
	return true;
}

int bdnE::InputManager::AddController()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	m_pControllers.push_back(std::make_unique<Controller>(index));
	m_ActionBindings.push_back(std::vector<std::pair<ControllerBinding,std::string>>{});
	return index;
}

void bdnE::InputManager::AddControllerBinding(ControllerButton button, KeyState keyState,
                                              std::shared_ptr<bdnE::Command> command, int controllerIdx, bdnE::Scene* scene) 
{
	AddControllerBinding(ControllerBinding{ button ,keyState,std::move(command)}, controllerIdx, scene);
}

void bdnE::InputManager::AddControllerBinding(const ControllerBinding& keyBind, int controllerIdx, bdnE::Scene* scene) 
{
	m_ActionBindings[controllerIdx].emplace_back(keyBind,scene->GetSceneName());
}

void bdnE::InputManager::AddKeyboardBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command, Scene* scene)
{
	AddKeyboardBinding({ button,keyState,command }, scene);
}

void bdnE::InputManager::AddKeyboardBinding(const KeyboardBinding& keyBind, Scene* scene)
{
	m_KeyBinds.emplace_back(keyBind, scene->GetSceneName());
}
