#pragma once
#include <chrono>
#include <thread>

#include "Singleton.h"


namespace bdnE
{
    class GameTime : public bdnE::Singleton<GameTime>
    {
    public:
        void Update()
        {
            const auto now = std::chrono::high_resolution_clock::now();
            const auto elapsed = now - m_LastTime;
            m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed).count();
            m_LastTime = now;
        }

        void SetMaxFPS(float newMax)
        {
            m_MaxFPS = newMax;
            m_MsPerFrame = 1000.f / m_MaxFPS;
        }

        float GetDeltaTime() { return m_DeltaTime; }
        float GetFixedTimeStep() { return m_FixedTimeStep; }
        float GetMaxFPS() { return m_MaxFPS; }
        float GetMsPerFrame() { return m_MsPerFrame; }

        void FPSDelay()
        {
            const auto frameEndTime = m_LastTime + std::chrono::milliseconds(static_cast<long long>(m_MsPerFrame));
            const auto now = std::chrono::high_resolution_clock::now();
            if (now < frameEndTime)
            {
                const auto timeToWait = frameEndTime - now;
                std::this_thread::sleep_for(timeToWait);
            }
        }




    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime = std::chrono::high_resolution_clock::now();
        float m_DeltaTime = 0.0f;
        float m_FixedTimeStep = 0.02f;
        float m_MaxFPS{ 60.f };
        float m_MsPerFrame{ 1000.f / m_MaxFPS };
    };
}


