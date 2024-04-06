#include "Controller.h"
#define WIN32_LEAN_AND_MEAN
#include <memory>
#include <windows.h>
#include <Xinput.h>
#include <vector>
#include "Command.h"


class bdnE::Controller::ControllerImpl final
{
public:
	explicit ControllerImpl(int controllerIndex)
		:m_ControllerIndex(controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}
	~ControllerImpl() = default;
	void HandleInputs()
	{
		//Set previous state from previous currentstate
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		//Get new state for controller with this index
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		//Get button changes
		const auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		//Go over all bindings & execute
		for (const auto& bind : m_ActionBindings)
		{
			switch (bind.keyState)
			{
			case KeyState::pressed:
				if ( static_cast<unsigned int>(bind.button) & m_CurrentState.Gamepad.wButtons)
				{
					bind.command->Execute();
				}
				break;
			case KeyState::pressedThisFrame:
				if (static_cast<unsigned int>(bind.button) & m_ButtonsPressedThisFrame)
				{
					bind.command->Execute();
				}
				break;
			case KeyState::releasedThisFrame:
				if (static_cast<unsigned int>(bind.button) & m_ButtonsReleasedThisFrame)
				{
					bind.command->Execute();
				}
				break;
			default:
				break;
			}
		}
	}

	void AddButtonBinding(ControllerButton button, KeyState keyState, std::shared_ptr<Command> command)
	{
		AddButtonBinding(ControllerBinding{ button,keyState,std::move( command) });
	}
	void AddButtonBinding(const ControllerBinding& keyBind)
	{
		m_ActionBindings.emplace_back(keyBind);
	}


private:

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	const int m_ControllerIndex;
	std::vector<ControllerBinding> m_ActionBindings{};

};

bdnE::Controller::Controller(int controllerIndex):m_pImpl{std::make_unique<ControllerImpl>(controllerIndex)}
{
}

bdnE::Controller::~Controller() = default;


void bdnE::Controller::HandleInputs()
{
	m_pImpl->HandleInputs();
}

void bdnE::Controller::AddButtonBinding(ControllerButton button, KeyState keyState, std::shared_ptr<bdnE::Command> command) const
{
	m_pImpl->AddButtonBinding(button, keyState, std::move(command));
}

void bdnE::Controller::AddButtonBinding(const ControllerBinding& keyBind) const
{
	m_pImpl->AddButtonBinding(keyBind);
}
