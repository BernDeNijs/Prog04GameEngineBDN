#pragma once
#include "GameComponent.h"
#include "../Observers/Subject.h"

namespace dae
{
	class ScoreComponent :public GameComponent, public Subject
	{
	public:

		explicit ScoreComponent(GameObject* owner) : GameComponent(owner)
		{
			m_EventData.emplace("ScoreComponent", this);
		}
		void GainScore(int amount)
		{
			m_Score += amount;
			Notify("PickedUpAnItem");
		}

		int GetScore() { return m_Score; }
	private:

		int m_Score = 3;

	};
}