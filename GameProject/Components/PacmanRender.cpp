#include "PacmanRender.h"
#include "GameObject.h"

bdnG::PacmanRender::PacmanRender(bdnE::GameObject* owner) : GameComponent(owner)
{
}

bdnG::PacmanRender::PacmanRender(bdnE::GameObject* owner, const std::shared_ptr<bdnE::Texture2D>& texture) : PacmanRender(owner)
{
    SetTexture(texture);
}

bdnG::PacmanRender::PacmanRender(bdnE::GameObject* owner, const std::string& texture) : PacmanRender(owner)
{
    SetTexture(texture);
}

void bdnG::PacmanRender::Render() const
{
    if (m_pTexture == nullptr) return;
    const auto transform = GetOwner()->GetWorldTransform();

    bdnE::Renderer::GetInstance().RenderTexture(*m_pTexture, transform,true);
}