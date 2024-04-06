#pragma once
#include "Buttons.h"
#include <memory>
#include <SDL.h>
#include <vector>

namespace bdnE
{
	struct KeyboardBinding
	{
		SDL_Scancode button{};
		KeyState keyState{};
		std::shared_ptr<Command> command{};
	};

	class KeyboardControl
	{
	public:


		explicit KeyboardControl();
		~KeyboardControl();

		KeyboardControl(KeyboardControl&) = delete;
		KeyboardControl(KeyboardControl&&) = delete;
		KeyboardControl& operator=(KeyboardControl&) = delete;
		KeyboardControl& operator=(KeyboardControl&&) = delete;

		void HandleInputs();
		void AddButtonBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command);
		void AddButtonBinding(const KeyboardBinding& keyBind);

	private:

		std::vector<KeyboardBinding> m_KeyBinds{};

		Uint8 m_PreviousState[SDL_NUM_SCANCODES]{};
		Uint8 m_CurrentState[SDL_NUM_SCANCODES]{};
	};



}

