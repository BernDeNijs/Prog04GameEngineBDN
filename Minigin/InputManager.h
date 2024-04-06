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
		Controller* AddController();
		KeyboardControl* GetKeyboardController() const { return m_Keyboard.get(); }
	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		std::unique_ptr<KeyboardControl> m_Keyboard{ std::make_unique<KeyboardControl>() };
	};

}
