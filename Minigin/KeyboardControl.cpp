#include "KeyboardControl.h"
#include "Command.h"
bdnE::KeyboardControl::KeyboardControl()
{
	memset(m_PreviousState, 0, SDL_NUM_SCANCODES * sizeof(Uint8));
	memset(m_CurrentState, 0, SDL_NUM_SCANCODES * sizeof(Uint8));
}

bdnE::KeyboardControl::~KeyboardControl()
{
}

void bdnE::KeyboardControl::HandleInputs()
{
    // Update the previous state
    memcpy(m_PreviousState, m_CurrentState, SDL_NUM_SCANCODES * sizeof(Uint8));

    // Get the current state
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    memcpy(m_CurrentState, state, SDL_NUM_SCANCODES * sizeof(Uint8));

    //// Process key events
    //for (const auto& bind : m_KeyBinds) {
    //    if ((m_CurrentState[bind.button] && bind.keyState == KeyState::pressed) ||
    //        (m_CurrentState[bind.button] && !m_PreviousState[bind.button] && bind.keyState == KeyState::pressedThisFrame) ||
    //        (!m_CurrentState[bind.button] && m_PreviousState[bind.button] && bind.keyState == KeyState::releasedThisFrame)) {
    //        bind.command->Execute();
    //    }
    //}
}

void bdnE::KeyboardControl::CheckBinding(const bdnE::KeyboardBinding& binding) const
{
    if ((m_CurrentState[binding.button] && binding.keyState == KeyState::pressed) ||
        (m_CurrentState[binding.button] && !m_PreviousState[binding.button] && binding.keyState == KeyState::pressedThisFrame) ||
        (!m_CurrentState[binding.button] && m_PreviousState[binding.button] && binding.keyState == KeyState::releasedThisFrame)) {
        binding.command->Execute();
    }
}

//void bdnE::KeyboardControl::AddButtonBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command)
//{
//	AddButtonBinding({ button,keyState,command });
//}
//
//void bdnE::KeyboardControl::AddButtonBinding( const KeyboardBinding& keyBind)
//{
//	m_KeyBinds.emplace_back(keyBind);
//}
