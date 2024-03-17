#include "KeyboardControl.h"
#include "Commands/Command.h"
KeyboardControl::KeyboardControl()
{
	memset(m_PreviousState, 0, SDL_NUM_SCANCODES * sizeof(Uint8));
	memset(m_CurrentState, 0, SDL_NUM_SCANCODES * sizeof(Uint8));
}

KeyboardControl::~KeyboardControl()
{
}

void KeyboardControl::HandleInputs()
{
    // Update the previous state
    memcpy(m_PreviousState, m_CurrentState, SDL_NUM_SCANCODES * sizeof(Uint8));

    // Get the current state
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    memcpy(m_CurrentState, state, SDL_NUM_SCANCODES * sizeof(Uint8));

    // Process key events
    for (const auto& bind : m_KeyBinds) {
        if ((m_CurrentState[bind.button] && bind.keyState == KeyState::pressed) ||
            (m_CurrentState[bind.button] && !m_PreviousState[bind.button] && bind.keyState == KeyState::pressedThisFrame) ||
            (!m_CurrentState[bind.button] && m_PreviousState[bind.button] && bind.keyState == KeyState::releasedThisFrame)) {
            bind.command->Execute();
        }
    }
}

void KeyboardControl::AddButtonBinding(SDL_Scancode button, KeyState keyState, std::shared_ptr<Command> command)
{
	AddButtonBinding({ button,keyState,command });
}

void KeyboardControl::AddButtonBinding( const KeyboardBinding& keyBind)
{
	m_KeyBinds.emplace_back(keyBind);
}
