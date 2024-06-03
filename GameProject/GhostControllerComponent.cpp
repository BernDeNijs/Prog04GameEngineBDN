
#include "GameObject.h"
#include "GhostControllerComponent.h"
#include "GhostState.h"
#include "GhostStateScatter.h"
#include "RenderComponent.h"

bdnG::GhostControllerComponent::GhostControllerComponent(bdnE::GameObject* owner, bdnE::GameObject* target) : GameComponent(owner)
{
	m_CurrentState = std::make_unique<GhostStateScatter>();
	m_pRenderer = owner->GetComponent<RenderComponent>();
	m_pTarget = target;

	m_CurrentState->Enter(m_pTarget);
}

void bdnG::GhostControllerComponent::Update()
{
	
	if (GhostState* state = m_CurrentState->Update(m_pOwner, m_pTarget); 
		state != m_CurrentState.get())
	{
		//We changed states
		//--trigger the exit of the current state
		m_CurrentState->Exit();
		//Set our new state
		m_CurrentState = std::move(std::unique_ptr<GhostState>(state));
		//Trigger the enter of our new state
		m_CurrentState->Enter(m_pTarget);
	}
}

void bdnG::GhostControllerComponent::Render() const
{
	if (m_pRenderer != nullptr)
	{
		m_CurrentState->Render(m_pRenderer);
	}
	
}

