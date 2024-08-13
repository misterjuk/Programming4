#include "ScoreComponent.h"
#include <fstream>
#include <iostream>

ScoreComponent::ScoreComponent(yev::GameObject* ownerObjectPtr)
    : yev::Component(ownerObjectPtr), m_currentScore(0), m_highScore(0)
{
    m_HighScoreText = m_Owner->GetComponent<yev::TextComponent>();

    LoadHighScore();
    
}

void ScoreComponent::SaveHighScore()
{
    std::ofstream file(m_highScoreFilePath);
    if (file.is_open())
    {
        file << m_highScore;
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for saving high score: " << m_highScoreFilePath << std::endl;
    }
}

void ScoreComponent::LoadHighScore()
{
    std::ifstream file(m_highScoreFilePath);
    if (file.is_open())
    {
        file >> m_highScore;

        m_HighScoreText->SetText("HighScore: " + std::to_string(m_highScore));
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for loading high score: " << m_highScoreFilePath << std::endl;
    }
}

void ScoreComponent::UpdateHighScore()
{
    if (m_currentScore > m_highScore)
    {
        m_highScore = m_currentScore;
        SaveHighScore();
    }
}
