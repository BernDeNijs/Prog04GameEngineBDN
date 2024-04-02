#include "RenderComponent.h"

dae::RenderComponent::RenderComponent(GameObject* owner) : GameComponent(owner)
{
}

dae::RenderComponent::RenderComponent(GameObject* owner, const std::shared_ptr<dae::Texture2D>& texture) : RenderComponent(owner) 
{ 
	SetTexture(texture); 
}

dae::RenderComponent::RenderComponent(GameObject* owner, const std::string& texture) : RenderComponent(owner) 
{ 
	SetTexture(texture); 
}

void dae::RenderComponent::Render() const
{
    if (m_pTexture == nullptr) return;

    glm::vec3 position = GetOwner()->GetWorldTransform().Position;
    dae::Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
}
