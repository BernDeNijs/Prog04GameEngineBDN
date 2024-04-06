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
		bool ProcessInput();
		static Controller* AddController();
		static KeyboardControl* GetKeyboardController() { return m_Keyboard.get(); }
	private:
		inline static std::vector<std::unique_ptr<Controller>> m_pControllers{};
		inline static std::unique_ptr<KeyboardControl> m_Keyboard{ std::make_unique<KeyboardControl>() };
	};

}
