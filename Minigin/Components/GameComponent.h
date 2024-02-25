#pragma once
#include "../GameObject.h"

namespace dae
{
	class GameComponent
	{
	public:
		GameComponent(GameObject* owner) :m_pOwner(owner) {}
		virtual ~GameComponent() = default;
		GameComponent(const GameComponent& other) = delete;
		GameComponent(GameComponent&& other) = delete;
		GameComponent& operator=(const GameComponent& other) = delete;
		GameComponent& operator=(GameComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;
		virtual void RenderImGui() = 0;

	protected:
		GameObject* m_pOwner = nullptr;
	};
}