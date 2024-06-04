#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Controller.h"
#include "Singleton.h"
#include "KeyboardControl.h"

namespace bdnE
{
	class Scene;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput() const;
		void SetActiveScene(const std::string& sceneName) { m_SceneName = sceneName; }
		void RemoveSceneInput(const std::string sceneName);

		//Controller functions
		int AddController();

		void AddControllerBinding(ControllerButton button, KeyState keyState, std::shared_ptr<bdnE::Command> command, int controllerIdx, Scene* scene) ;
		void AddControllerBinding(const ControllerBinding& keyBind, int controllerIdx, Scene* scene) ;


		//Keyboard functions
		//KeyboardControl* GetKeyboardController() const { return m_Keyboard.get(); }

		void AddKeyboardBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command, Scene* scene);
		void AddKeyboardBinding(const KeyboardBinding& keyBind, Scene* scene);
	private:
		//Controller variables
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		std::vector<std::map<std::string, std::vector<ControllerBinding>>> m_ControllerBindings{};

		//Keyboard variables
		std::unique_ptr<KeyboardControl> m_Keyboard{ std::make_unique<KeyboardControl>() };
		std::map<std::string,std::vector<KeyboardBinding>> m_KeyboardBindings{};
		std::string m_SceneName = "";
	};

}
