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

		if (const auto it = m_ControllerBindings[i].find(m_SceneName);
			it != m_ControllerBindings[i].end()) {
			// If the scene name exists, iterate over the bindings
			for (const auto& binding : it->second) {
				m_pControllers[i]->CheckBinding(binding);
			}
		}
	}
	for (const auto& pController : m_pControllers)
	{
		pController->HandleInputs();
	}
	//Handle keyboard events
	m_Keyboard->HandleInputs();
	
	if (const auto it = m_KeyboardBindings.find(m_SceneName);
		it != m_KeyboardBindings.end()) {
		// If the scene name exists, iterate over the bindings
		for (const auto& binding : it->second) {
			m_Keyboard->CheckBinding(binding);
		}
	}
	return true;
}

void bdnE::InputManager::RemoveSceneInput(const std::string sceneName)
{
	////Remove keyboard controls linked to scene
	auto keyboardIt = m_KeyboardBindings.find(sceneName);
	if (keyboardIt != m_KeyboardBindings.end()) {
		m_KeyboardBindings.erase(keyboardIt);
	}

	//Remove controller controls linked to scene
	for (int i = 0; i < static_cast<int>(m_ControllerBindings.size()); i++)
	{
		auto controllerIt = m_ControllerBindings[i].find(sceneName);
		if (controllerIt != m_ControllerBindings[i].end()) {
			m_ControllerBindings[i].erase(controllerIt);
		}
	}
}

int bdnE::InputManager::AddController()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	m_pControllers.push_back(std::make_unique<Controller>(index));
	m_ControllerBindings.push_back(std::map<std::string, std::vector<ControllerBinding>>{});
	return index;
}

void bdnE::InputManager::AddControllerBinding(ControllerButton button, KeyState keyState,
                                              std::shared_ptr<bdnE::Command> command, int controllerIdx, bdnE::Scene* scene) 
{
	AddControllerBinding(ControllerBinding{ button ,keyState,std::move(command)}, controllerIdx, scene);
}

void bdnE::InputManager::AddControllerBinding(const ControllerBinding& keyBind, int controllerIdx, bdnE::Scene* scene) 
{
	m_ControllerBindings[controllerIdx][scene->GetSceneName()].emplace_back(keyBind);
}

void bdnE::InputManager::AddKeyboardBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command, Scene* scene)
{
	AddKeyboardBinding({ button,keyState,command }, scene);
}

void bdnE::InputManager::AddKeyboardBinding(const KeyboardBinding& keyBind, Scene* scene)
{
	const std::string& sceneName = scene->GetSceneName();
	m_KeyboardBindings[sceneName].push_back(keyBind);

	//m_KeyboardBindings.insert({ scene->GetSceneName(), keyBind });
	//m_KeyboardBindings.emplace_back(keyBind, scene->GetSceneName());
}
