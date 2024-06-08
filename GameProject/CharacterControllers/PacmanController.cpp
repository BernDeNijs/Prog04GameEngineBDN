#include "PacmanController.h"

#include "InputManager.h"
#include "../Components/PacmanMovement.h"
#include "../Commands/PacmanMoveCommand.h"
#include "../Components/CircleCollider.h"

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

	auto collider = m_pOwner->AddComponent<CircleCollider>(5.f, "Pacman");
	collider->AddCollisionLayer("Ghost");
	collider->AddObserver(this);

}

void bdnG::PacmanController::OnNotify(const std::string& eventName,
	const std::unordered_map<std::string, std::any>& eventData)
{
	if (eventName == "CollisionStay")
	{
		auto iter = eventData.find("other");
		if (iter != eventData.end()) {
			CollidedWithPlayer(std::any_cast<CircleCollider*>(iter->second));
		}
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

void bdnG::PacmanController::CollidedWithPlayer(CircleCollider* /*other*/)
{
	Notify("PlayerHitByGhost");
}
