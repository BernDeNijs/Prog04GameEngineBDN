#include "SDLSoundService.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <deque>
#include <mutex>
#include <unordered_map>


struct SoundLoadData
{
	std::string path = " ";
	int id = -1;
	bool initialized = false;
};


struct PlaySoundData
{
	int soundId = -1;
	int volume = 100;
	int nrOfLoops = 0;
	int channel = 0;
};

//IMPL CLASS
class bdnE::SDLSoundService::SoundImpl final
{
public:
	explicit SoundImpl(int nrOfChannels)
	{
		m_NrOfChannels = std::max(nrOfChannels,1); //minimum 1 channel

		if (SDL_Init(SDL_INIT_AUDIO) == -1)
		{

			std::cout << "Audio system not initialized: " << SDL_GetError() << '\n';
		}
			
		if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, m_NrOfChannels, 2048) == -1)
		{
			std::cout << "Audio device not initialized: " << Mix_GetError() << '\n';
		}
		//Create seperate thread for sound
		//--Single thread implementation
		m_SoundThreads.emplace_back(std::jthread{ [&] { SoundThread(); } });
		//m_SoundsToPlay.push_back(std::deque<PlaySoundData>());

		////--Multiple thread implementation
		//for (int i = 0; i < m_NrOfChannels; i++)
		//{
		//	m_SoundThreads.emplace_back ( std::jthread{ [&] { SoundThread(); } });
		//	m_SoundsToPlay.push_back(std::deque<PlaySoundData>());
		//}
		//m_SoundsToPlay.resize(m_NrOfChannels);
		m_LoadThread = std::jthread{ [&] { LoadThread(); } };
		
	}
	~SoundImpl()
	{
		for (auto& sound : m_RegisteredSounds)
		{
			Mix_FreeChunk(sound.second);
		}
		m_Continue = false; //Stop threaded function
		Mix_CloseAudio();
	}

	SoundImpl(SoundImpl&) = delete;
	SoundImpl(SoundImpl&&) = delete;
	SoundImpl& operator=(SoundImpl&) = delete;
	SoundImpl& operator=(SoundImpl&&) = delete;

	void AddSoundToLoadQueue(SoundLoadData const data)
	{
		m_SoundsToLoad.emplace_back(data);
	}
	void LoadSound( SoundLoadData const& data)
	{
		
		if (const auto it = m_RegisteredSounds.find(data.id); 
			it != m_RegisteredSounds.end())
		{
			Mix_FreeChunk(m_RegisteredSounds[data.id]); //If already a sound inside the key free it for overwrite
		}

		Mix_Chunk* soundChunk{ Mix_LoadWAV(("..\\Data\\Sound\\" + data.path).c_str()) };
		if (soundChunk == nullptr)
		{
			std::cout << "Failed to load sound for path: " + data.path + "\n";
		}
		m_RegisteredSounds.emplace(data.id, soundChunk);
		std::cout << "loaded sound" << data.path << "at id: " << data.id << "\n";

	}
	void AddSoundToQueue(int soundId , int channel , int volume , int nrOfLoops)
	{
		if (channel > m_NrOfChannels)
		{
			printf(("Tried to add sound to nonexistent channel\n "));
			return;
		}

		const PlaySoundData newSound{ soundId, volume, nrOfLoops, channel }; //create new sound
		m_SoundsToPlay.push_back(newSound);

	}
	void SoundThread()
	{
		m_ChannelMutex.lock();
		const int threadChannel = m_CreatedChannels;
		m_CreatedChannels++;
		std::cout << "Thread created for channel" << threadChannel << "\n";
		m_ChannelMutex.unlock();
		
		while (m_Continue) //Keep thread going while class exists
		{
			PlaySoundData sound;
			//Start mutex
			m_SoundQueueMutex.lock();
			if ((!m_SoundsToPlay.empty()) 
				&& m_SoundsToLoad.empty())
			{
				sound = m_SoundsToPlay.front();

				m_SoundsToPlay.pop_front();
				
				//end mutex			
			}
			m_SoundQueueMutex.unlock();

			if (sound.soundId != -1)
			{

				PlaySound(sound);
			}

		}
	}
	void LoadThread()
	{
		thread_local SoundLoadData soundToLoad;
		while (m_Continue) //Keep thread going while class exists
		{
			//Start mutex
			
			m_SoundLoadQueueMutex.lock();
			if (!m_SoundsToLoad.empty())
			{
				soundToLoad = m_SoundsToLoad.front();
				soundToLoad.initialized = true;
				LoadSound(soundToLoad);
				soundToLoad.initialized = false;
				m_SoundsToLoad.pop_front();										
			}
			m_SoundLoadQueueMutex.unlock();

			//if (soundToLoad.initialized)
			//{


			//}
		}
	}
	void PlaySound(const PlaySoundData& sound) const
	{

		if (const auto it = m_RegisteredSounds.find(sound.soundId);
			it == m_RegisteredSounds.end())
		{
			//sound not found
			return;
		}

		//Set new volume
		const int volume = std::clamp(sound.volume, 0, MIX_MAX_VOLUME);
		Mix_Volume(sound.channel, volume); // -1 for all channels

		//Play sound		
		Mix_PlayChannel(sound.channel, m_RegisteredSounds.at(sound.soundId), sound.nrOfLoops); //-1 for all channels
	}

private:
	int m_NrOfChannels{ 0 };
	bool m_Continue{ true };
	std::vector<std::jthread> m_SoundThreads{};
	std::jthread m_LoadThread{};
	std::deque<SoundLoadData> m_SoundsToLoad{};
	std::unordered_map<int, Mix_Chunk*> m_RegisteredSounds{};
	std::deque<PlaySoundData> m_SoundsToPlay{};

	int m_CreatedChannels{ 0 };

	std::mutex m_SoundQueueMutex{};
	std::mutex m_SoundLoadQueueMutex{};
	std::mutex m_ChannelMutex{};
	
};



//CLASS FUNCTIONS

bdnE::SDLSoundService::SDLSoundService(int nrOfChannels):m_pImpl { std::make_unique<SoundImpl>(nrOfChannels) }
{
}

bdnE::SDLSoundService::~SDLSoundService() = default;



void bdnE::SDLSoundService::PlaySound(int soundId, int channel, int volume, int nrOfLoops /* - 1 for infinite*/)
{
	m_pImpl->AddSoundToQueue(soundId, channel, volume, nrOfLoops);
}

void bdnE::SDLSoundService::LoadSound(std::string path, int id)
{
	SoundLoadData data;
	data.id = id;
	data.path = path;
	m_pImpl->AddSoundToLoadQueue(data);
}
