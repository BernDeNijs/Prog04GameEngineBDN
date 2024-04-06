#pragma once
class Orbit_Component
{
};

#pragma once
#include "GameComponent.h"
#include <numbers>
#define TWO_PI 2.f * std::numbers::pi_v<float>

namespace bdnG
{
	class OrbitComponent : public bdnE::GameComponent
	{
	public:
		explicit OrbitComponent(bdnE::GameObject* owner);
		explicit OrbitComponent(bdnE::GameObject* owner, float radius, float speed);
		void Update() override;


	private:
		float m_Radius = 0.0f;
		float m_Speed = 0.0f;
		float m_Angle = 0.0f;
	};
}


