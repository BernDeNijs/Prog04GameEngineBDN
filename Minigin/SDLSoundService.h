#pragma once
#include <memory>
#include <string>
#include "SoundService.h"

namespace bdnE
{

	class SDLSoundService : public SoundService
	{
	public:


		explicit SDLSoundService(int nrOfChannels);
		virtual ~SDLSoundService();

		SDLSoundService(SDLSoundService&) = delete;
		SDLSoundService(SDLSoundService&&) = delete;
		SDLSoundService& operator=(SDLSoundService&) = delete;
		SDLSoundService& operator=(SDLSoundService&&) = delete;

		virtual void PlaySound(int soundId, int channel, int volume, int nrOfLoops) override;
		virtual void LoadSound(std::string path, int id) override;


	private:
		class SoundImpl;
		std::unique_ptr<SoundImpl> m_pImpl;

	};
}

