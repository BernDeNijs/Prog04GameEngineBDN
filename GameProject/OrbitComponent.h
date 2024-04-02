#pragma once
class Orbit_Component
{
};

#pragma once
#include "GameComponent.h"
#include <numbers>
#define TWO_PI 2.f * std::numbers::pi_v<float>

namespace dae
{
	class OrbitComponent : public dae::GameComponent
	{
	public:
		explicit OrbitComponent(GameObject* owner);
		explicit OrbitComponent(GameObject* owner, float radius, float speed);
		void Update() override;


	private:
		float m_Radius = 0.0f;
		float m_Speed = 0.0f;
		float m_Angle = 0.0f;
	};
}


