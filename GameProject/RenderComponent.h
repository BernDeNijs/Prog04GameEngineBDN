#pragma once
#include "GameComponent.h"
#include <glm/vec3.hpp>
#include "Renderer.h"
#include "ResourceManager.h"

namespace bdnG
{
    class RenderComponent :public bdnE::GameComponent
    {
    public:
        explicit RenderComponent(bdnE::GameObject* owner);
        explicit RenderComponent(bdnE::GameObject* owner, const std::shared_ptr<bdnE::Texture2D>& texture);
        explicit RenderComponent(bdnE::GameObject* owner, const std::string& texture);

        void Render() const override;

        void SetTexture(const std::shared_ptr<bdnE::Texture2D>& texture) {   m_pTexture = texture;   }
        void SetTexture(const std::string& filename)    {   m_pTexture = bdnE::ResourceManager::GetInstance().LoadTexture(filename);  }

    private:
        std::shared_ptr<bdnE::Texture2D> m_pTexture;
    };
}