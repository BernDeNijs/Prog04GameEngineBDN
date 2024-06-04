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
    const glm::vec3 position = transform.Position;
    const auto scale = transform.Scale;
    
    bdnE::Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y, scale.x, scale.y);
}
