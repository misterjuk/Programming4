#include "GameTime.h"

void GameTime::Start()
{
	m_startTime = std::chrono::high_resolution_clock::now();
}

void GameTime::Update()
{
    const auto currentTime = std::chrono::high_resolution_clock::now();
    float currentDeltaTime = std::chrono::duration<float>(currentTime - m_lastTime).count();

    // Cap the delta time to a maximum value (e.g., 10 seconds)
    const float maxDeltaTime = 10.0f;
    currentDeltaTime = std::min(currentDeltaTime, maxDeltaTime);

    // Store the current delta time in the buffer
    m_DeltaTimeBuffer[m_CurrentIndex] = currentDeltaTime;

    // Move to the next index in the circular buffer
    m_CurrentIndex = (m_CurrentIndex + 1) % m_DeltaTimeBuffer.size();

    // Calculate the average delta time
    float averageDeltaTime = 0.0f;
    for (float dt : m_DeltaTimeBuffer)
    {
        averageDeltaTime += dt;
    }
    averageDeltaTime /= m_DeltaTimeBuffer.size();

    // Set the average delta time as the actual delta time
    m_DeltaTime = averageDeltaTime;

    m_lastTime = currentTime;
}