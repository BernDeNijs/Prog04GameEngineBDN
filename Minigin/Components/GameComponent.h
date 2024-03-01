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

		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void FixedUpdate() {}
		virtual void Render() const {}
		virtual void RenderImGui() {}

		GameObject* GetOwner() const { return m_pOwner; }
	protected:
		GameObject* m_pOwner = nullptr;
	};
}