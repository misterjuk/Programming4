#pragma once

#include "GameObject.h"
#include "Component.h"
#include <string>
#include "TextComponent.h"
class ScoreComponent final : public yev::Component
{
public:
    ScoreComponent(yev::GameObject* ownerObjectPtr);
    ~ScoreComponent() = default;

    ScoreComponent(const ScoreComponent&) = delete;
    ScoreComponent(ScoreComponent&&) = delete;
    ScoreComponent& operator=(const ScoreComponent&) = delete;
    ScoreComponent& operator=(ScoreComponent&&) = delete;

    // Method to get the current score
    int GetCurrentScore() const { return m_currentScore; }

    // Method to add to the current score
    void AddScore(int score) { m_currentScore += score; }

    // Method to save the high score to a file
    void SaveHighScore();

    // Method to load the high score from a file
    void LoadHighScore();

private:
    // Path to the high score file
    const std::string m_highScoreFilePath = "../Data/highscore.txt";

    // Current score of the player
    int m_currentScore;

    // High score loaded from the file
    int m_highScore;

    yev::TextComponent* m_HighScoreText{nullptr};
    // Method to update high score if the current score is higher
    void UpdateHighScore();
};
