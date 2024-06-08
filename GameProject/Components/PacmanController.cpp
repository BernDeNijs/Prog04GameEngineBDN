#include "PacmanController.h"

#include "InputManager.h"
#include "PacmanMovement.h"
#include "../Commands/PacmanMoveCommand.h"

bdnG::PacmanController::PacmanController(bdnE::GameObject* owner, int id):GameComponent(owner), m_Id{id}
{
	if (m_Id == 0)
	{
		BindKeyboardControls();
	}
	else
	{
		BindControllerControls();
	}
}

void bdnG::PacmanController::BindKeyboardControls()
{
	auto& inputManager = bdnE::InputManager::GetInstance();
	inputManager.AddKeyboardBinding(SDL_SCANCODE_W, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::up), m_pOwner->GetScene());
	inputManager.AddKeyboardBinding(SDL_SCANCODE_S, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::down), m_pOwner->GetScene());
	inputManager.AddKeyboardBinding(SDL_SCANCODE_A, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::left), m_pOwner->GetScene());
	inputManager.AddKeyboardBinding(SDL_SCANCODE_D, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::right), m_pOwner->GetScene());
}

void bdnG::PacmanController::BindControllerControls()
{
	auto& inputManager = bdnE::InputManager::GetInstance();
	inputManager.AddControllerBinding(bdnE::ControllerButton::DPadUp, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::up),0, m_pOwner->GetScene());
	inputManager.AddControllerBinding(bdnE::ControllerButton::DPadDown, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::down),0, m_pOwner->GetScene());
	inputManager.AddControllerBinding(bdnE::ControllerButton::DPadLeft, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::left),0, m_pOwner->GetScene());
	inputManager.AddControllerBinding(bdnE::ControllerButton::DPadRight, bdnE::KeyState::pressed, std::make_shared<bdnG::PacmanMoveCommand>(m_pOwner, bdnG::MoveDirections::right),0, m_pOwner->GetScene());
}
