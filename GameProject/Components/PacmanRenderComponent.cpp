#include "PacmanRenderComponent.h"
#include "GameObject.h"

bdnG::PacmanRenderComponent::PacmanRenderComponent(bdnE::GameObject* owner) : GameComponent(owner)
{
}

bdnG::PacmanRenderComponent::PacmanRenderComponent(bdnE::GameObject* owner, const std::shared_ptr<bdnE::Texture2D>& texture) : PacmanRenderComponent(owner)
{
    SetTexture(texture);
}

bdnG::PacmanRenderComponent::PacmanRenderComponent(bdnE::GameObject* owner, const std::string& texture) : PacmanRenderComponent(owner)
{
    SetTexture(texture);
}

void bdnG::PacmanRenderComponent::Render() const
{
    if (m_pTexture == nullptr) return;
    const auto transform = GetOwner()->GetWorldTransform();

    bdnE::Renderer::GetInstance().RenderTexture(*m_pTexture, transform,true);
}