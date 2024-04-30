#pragma once
#include <memory>
#include "SoundService.h"
#include "NullSoundService.h"
namespace bdnE
{
	class SoundLocator final
	{

	public:
		static bdnE::SoundService& get_sound_system() { return *m_SsInstance; }
		static void register_sound_system(std::unique_ptr<bdnE::SoundService>&& ss) { m_SsInstance = std::move(ss); }

	private:
		inline static std::unique_ptr<bdnE::SoundService> m_SsInstance{ std::make_unique<bdnE::NullSoundService>() };

	};
}

