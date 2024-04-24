#pragma once
#include "Buttons.h"
#include <memory>
namespace bdnE
{

	enum class ControllerButton
	{
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,

		Start = 0x0010,
		Back = 0x0020,

		LeftThumbstick = 0x0040,
		RightThumbstick = 0x0080,

		LeftBumper = 0x0100,
		RightBumper = 0x0200,

		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
	};

	struct ControllerBinding
	{
		ControllerButton button{};
		KeyState keyState{};
		std::shared_ptr<Command> command{};
	};

	class Controller final
	{
	public:


		explicit Controller(int controllerIndex);
		~Controller();

		Controller(Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(Controller&) = delete;
		Controller& operator=(Controller&&) = delete;

		void HandleInputs();
		void AddButtonBinding(ControllerButton button, KeyState keyState, std::shared_ptr<bdnE::Command> command) const;
		void AddButtonBinding(const ControllerBinding& keyBind) const;

	private:

		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl;
	};
}