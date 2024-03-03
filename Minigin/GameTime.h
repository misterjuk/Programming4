#pragma once
#include <chrono>

#include "Singleton.h"

class GameTime final : public dae::Singleton<GameTime>
{
public:
    void Start();
    void Update();

    float GetDeltaTime() const { return m_DeltaTime; }
    float GetFixedDeltaTime() const { return m_FixedTimeStep; }

private:
    friend class Singleton<GameTime>;
    GameTime() = default;

    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_lastTime;
    float m_DeltaTime{};
    float m_FixedDeltaTime{};
    const float m_FixedTimeStep{ 0.1f };

};