#pragma once
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>

#include "GameComponent.h"

namespace dae
{
    class TransformComponent : public dae::GameComponent {
    private:
        glm::vec3 m_Position;
    public:
       

        explicit TransformComponent(GameObject* owner) : TransformComponent(owner, { 0, 0, 0 }) {}
        explicit TransformComponent(GameObject* owner, glm::vec3 position) : GameComponent(owner), m_Position(position) {}
        explicit TransformComponent(GameObject* owner, glm::vec2 position) : TransformComponent(owner, { position.x,position.y,0 }) {}

        glm::vec3 GetTransform() const { return m_Position; }
        void SetTransform(glm::vec3 position) { m_Position = position; }
        void SetTransform(glm::vec2 position) { SetTransform({position.x,position.y,0}); }
    };
}
