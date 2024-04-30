#pragma once
#include <string>
namespace bdnE
{
	class SoundService
	{
	public:
		explicit SoundService() = default;
		virtual ~SoundService() = default;

		SoundService(SoundService&) = delete;
		SoundService(SoundService&&) = delete;
		SoundService& operator=(SoundService&) = delete;
		SoundService& operator=(SoundService&&) = delete;

		virtual void PlaySound(int soundId, int channel, int volume, int nrOfLoops) = 0;
		virtual void LoadSound(std::string path, int id) = 0;
	};
}


