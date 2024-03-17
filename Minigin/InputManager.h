#pragma once
#include <memory>
#include <vector>

#include "Controller.h"
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		static Controller* AddController();

	private:
		inline static std::vector<std::unique_ptr<Controller>> m_pControllers{};
	};

}
