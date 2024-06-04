#pragma once
#include <memory>
#include <vector>

#include "Controller.h"
#include "Singleton.h"
#include "KeyboardControl.h"

namespace bdnE
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput() const;
		
		

		//Controller functions
		int AddController();

		void AddButtonBinding(ControllerButton button, KeyState keyState, std::shared_ptr<bdnE::Command> command, int controllerIdx) ;
		void AddButtonBinding(const ControllerBinding& keyBind, int controllerIdx) ;


		//Keyboard functions
		KeyboardControl* GetKeyboardController() const { return m_Keyboard.get(); }

		void AddKeyboardBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command);
		void AddKeyboardBinding(const KeyboardBinding& keyBind);
	private:
		//Controller variables
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		std::vector<std::vector<ControllerBinding>> m_ActionBindings{};

		//Keyboard variables
		std::unique_ptr<KeyboardControl> m_Keyboard{ std::make_unique<KeyboardControl>() };
		std::vector<KeyboardBinding> m_KeyBinds{};

	};

}
