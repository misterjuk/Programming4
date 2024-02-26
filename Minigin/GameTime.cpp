#include "GameTime.h"

void GameTime::Start()
{
	m_startTime = std::chrono::high_resolution_clock::now();
}

void GameTime::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_lastTime).count();
	m_lastTime = currentTime;
}