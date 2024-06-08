#pragma once
#include "GameComponent.h"
#include "Subject.h"

class PacmanController
{
};
namespace bdnG
{
	class CircleCollider;

	class PacmanController final : public bdnE::GameComponent, public bdnE::Subject, public bdnE::Observer
	{
	public:
		explicit PacmanController(bdnE::GameObject* owner, int id);
		int GetId() { return m_Id; }

		virtual void OnNotify(const std::string& eventName, const std::unordered_map<std::string, std::any>& eventData) override;

	private:
		void BindKeyboardControls();
		void BindControllerControls();
		const int m_Id;
		void CollidedWithPlayer(CircleCollider* other);
	};

}
