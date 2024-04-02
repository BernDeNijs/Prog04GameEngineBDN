#pragma once
#include "GameComponent.h"
#include <glm/vec3.hpp>
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    class RenderComponent :public GameComponent
    {
    public:
        explicit RenderComponent(GameObject* owner);
        explicit RenderComponent(GameObject* owner, const std::shared_ptr<dae::Texture2D>& texture);
        explicit RenderComponent(GameObject* owner, const std::string& texture);

        void Render() const override;

        void SetTexture(const std::shared_ptr<dae::Texture2D>& texture) {   m_pTexture = texture;   }
        void SetTexture(const std::string& filename)    {   m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);  }

    private:
        std::shared_ptr<dae::Texture2D> m_pTexture;
    };
}