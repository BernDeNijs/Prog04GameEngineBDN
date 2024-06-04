#include "RenderComponent.h"
#include "GameObject.h"

bdnG::RenderComponent::RenderComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
}

bdnG::RenderComponent::RenderComponent(bdnE::GameObject* owner, const std::shared_ptr<bdnE::Texture2D>& texture) : RenderComponent(owner)
{ 
	SetTexture(texture); 
}

bdnG::RenderComponent::RenderComponent(bdnE::GameObject* owner, const std::string& texture) : RenderComponent(owner)
{ 
	SetTexture(texture); 
}

void bdnG::RenderComponent::Render() const
{
    if (m_pTexture == nullptr) return;
    const auto transform = GetOwner()->GetWorldTransform();
    
    bdnE::Renderer::GetInstance().RenderTexture(*m_pTexture, transform);
}
