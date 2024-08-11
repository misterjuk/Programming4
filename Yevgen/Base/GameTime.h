#pragma once
#include <chrono>

#include "Singleton.h"
#include <array>

class GameTime final : public yev::Singleton<GameTime>
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

    std::array<float, 10> m_DeltaTimeBuffer;
    size_t m_CurrentIndex = 0;

};