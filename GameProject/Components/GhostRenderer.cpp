#include "GhostRenderer.h"
#include "GameObject.h"

bdnG::GhostRenderer::GhostRenderer(bdnE::GameObject* owner) : GameComponent(owner)
{
}

bdnG::GhostRenderer::GhostRenderer(bdnE::GameObject* owner, const std::shared_ptr<bdnE::Texture2D>& texture) : GhostRenderer(owner)
{
    SetTexture(texture);
}

bdnG::GhostRenderer::GhostRenderer(bdnE::GameObject* owner, const std::string& texture) : GhostRenderer(owner)
{
    SetTexture(texture);
}

void bdnG::GhostRenderer::Render() const
{
    if (m_pTexture == nullptr) return;
    const auto transform = GetOwner()->GetWorldTransform();

    //TODO: select texture from state

    //const SDL_Rect* srcRect;

    //switch (m_CurrentRenderState)
    //{
    //case bdnG::GhostRenderState::normal:
    //    break;
    //case bdnG::GhostRenderState::dead:
    //    break;
    //case bdnG::GhostRenderState::frightened:
    //    break;
    //default:
    //    break;
    //}

    bdnE::Renderer::GetInstance().RenderTexture(*m_pTexture, transform,  true);
}

void bdnG::GhostRenderer::SetRenderState(GhostRenderState state)
{
    m_CurrentRenderState = state;
}
