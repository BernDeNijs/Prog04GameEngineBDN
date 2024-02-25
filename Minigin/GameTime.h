#pragma once
#include <chrono>
#include <thread>

#include "Singleton.h"



class GameTime : public dae::Singleton<GameTime>
{
public:


    static void Update()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto elapsed = now - m_LastTime;
        m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed).count();
        m_LastTime = now;
    }

    static void SetMaxFPS(float newMax)
    {
        m_MaxFPS = newMax ;
        m_MsPerFrame = 1000.f / m_MaxFPS ;
    }

    static float GetDeltaTime() { return m_DeltaTime; }
    static float GetFixedTimeStep()  { return m_FixedTimeStep; }
    static float GetMaxFPS()  { return m_MaxFPS; }
    static float GetMsPerFrame()  { return m_MsPerFrame; }
    
    static void FPSDelay()
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
    inline static std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime = std::chrono::high_resolution_clock::now();
    inline static float m_DeltaTime = 0.0f;
    inline static float m_FixedTimeStep = 0.02f;
    inline static float m_MaxFPS{ 60.f };
    inline static float m_MsPerFrame{ 1000.f / m_MaxFPS };


};

