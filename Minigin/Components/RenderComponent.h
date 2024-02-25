#pragma once
#include "GameComponent.h"
#include<glm/vec3.hpp>
#include "../Renderer.h"
#include "../ResourceManager.h"
#include "TransformComponent.h"

namespace dae
{
    class RenderComponent :public GameComponent
    {
    public:
        explicit RenderComponent(GameObject* owner) : GameComponent(owner) 
        { 
            
            m_TransformComponent = owner->GetTransform();
            
           
        }
        explicit RenderComponent(GameObject* owner, const std::shared_ptr<dae::Texture2D>& texture) : RenderComponent(owner) { SetTexture(texture); }
        explicit RenderComponent(GameObject* owner, const std::string& texture) : RenderComponent(owner) { SetTexture(texture); }


        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}
        void Render() const override
        {
            const auto position = m_TransformComponent->GetTransform();
            dae::Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
        }
        void RenderImGui() override {}

        void SetTexture(const std::shared_ptr<dae::Texture2D>& texture)
        {
            m_pTexture = texture;
        }; 
        void SetTexture(const std::string& filename)
        {
            m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
        };

    private:
        std::shared_ptr<dae::Texture2D> m_pTexture;
        std::shared_ptr<TransformComponent> m_TransformComponent;

    };
}