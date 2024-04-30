#pragma once
#include "SoundService.h"

namespace bdnE
{
	class NullSoundService final : public SoundService
	{
	public:
		void PlaySound(int , int , int, int ) override
		{

		}
		void LoadSound(std::string , int ) override
		{

		}
	};
}


