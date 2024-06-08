#include "GameObject.h"
#include "GhostController.h"
#include "../GhostStates/GhostState.h"
#include "../GhostStates/GhostStateScatter.h"
#include "../Components/PacmanMovement.h"
#include "../Components/PickUp.h"

bdnG::GhostController::GhostController(bdnE::GameObject* owner, bdnE::GameObject* target) : GameComponent(owner)
{

	m_MovementComponent = owner->GetComponent<PacmanMovement>();


	m_CurrentState = std::make_unique<GhostStateScatter>();
	m_pRenderer = owner->GetComponent<GhostRenderer>();
	if (m_pRenderer == nullptr)
	{

	}
	m_pTarget = target;


	//Find power pellets
	std::vector<bdnE::GameObject*> sceneObjects = m_pOwner->GetScene()->GetAllObjectsInScene();


	for (const auto& object : sceneObjects)
	{
		const auto pickupComponent = object->GetComponent<PickUp>();
		if (pickupComponent == nullptr) continue;
		if (pickupComponent->GetType() == ItemType::powerPellet)
		{
			m_PowerPellets.push_back(pickupComponent);
		}
	}


	m_CurrentState->Enter(m_pTarget, m_PowerPellets);

}

void bdnG::GhostController::Update()
{

	if (GhostState* state = m_CurrentState->Update(m_pOwner, m_pTarget, m_MovementComponent);
		state != m_CurrentState.get())
	{
		//We changed states
		//--trigger the exit of the current state
		m_CurrentState->Exit(m_PowerPellets);
		//Set our new state
		m_CurrentState = std::move(std::unique_ptr<GhostState>(state));
		//Trigger the enter of our new state
		m_CurrentState->Enter(m_pTarget, m_PowerPellets);
	}
}

void bdnG::GhostController::Render() const
{
	if (m_pRenderer != nullptr)
	{
		m_CurrentState->Render(m_pRenderer);
	}

}