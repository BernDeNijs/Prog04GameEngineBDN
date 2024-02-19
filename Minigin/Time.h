#pragma once
#include <chrono>
#include "Singleton.h"


class Time : public dae::Singleton<Time>
{
    void Update(std::chrono::time_point<std::chrono::high_resolution_clock> now)
    {
        auto duration = now - lastTime;
        deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
        lastTime = now;
    }

    float GetDeltaTime() const
    {
        return deltaTime;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f;
};

