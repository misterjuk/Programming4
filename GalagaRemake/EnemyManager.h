#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"
#include <vector>       
#include <fstream>      
#include <sstream>      
#include <string>       
#include <iostream>
#include "IObserver.h"
#include "Singleton.h" // Include the Singleton template

   
class EnemyManager final : public yev::Singleton<EnemyManager>, public yev::IObserver
{
    friend class yev::Singleton<EnemyManager>;
public:
   
    ~EnemyManager() {
        // Clean up dynamically allocated enemies
        for (Enemy* enemy : m_Enemies) {
            delete enemy;
        }
        m_Enemies.clear();
    }

    EnemyManager(const EnemyManager& other) = delete;
    EnemyManager& operator=(const EnemyManager& other) = delete;
    EnemyManager(EnemyManager&& other) noexcept = delete;
    EnemyManager& operator=(EnemyManager&& other) noexcept = delete;

    // Load enemies from file
    void LoadEnemiesFromFile(const std::string& filename)
    {
        std::ifstream file(m_DataPath + filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        // Clear existing enemies
        for (Enemy* enemy : m_Enemies) {
            delete enemy;
        }
        m_Enemies.clear();

        // Read new enemies from file
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int x, y;
            std::string typeStr;
            EnemyType type;

            if (!(iss >> x >> y >> typeStr)) {
                std::cerr << "Error parsing line: " << line << std::endl;
                continue; // Skip invalid lines
            }

            if (typeStr == "Bee") {
                type = EnemyType::Bee;
            }
            else if (typeStr == "Butterfly") {
                type = EnemyType::Butterfly;
            }
            else if (typeStr == "Boss") {
                type = EnemyType::Boss;
            }
            else {
                std::cerr << "Unknown enemy type: " << typeStr << std::endl;
                continue; // Skip unknown types
            }

            m_Enemies.emplace_back(new Enemy(glm::vec3(x, y, 0), type));
        }
        file.close();
    }

    void Notify(IObserver::Event event, yev::GameObject* actor) override;

    const std::vector<Enemy*>& GetEnemies() const { return m_Enemies; };
private:
    // Constructor with custom data path
    EnemyManager(const std::string& dataPath) : m_DataPath{ dataPath } {}

    // Default constructor with default data path
    EnemyManager() : m_DataPath{ "Data/" } {}


    std::vector<Enemy*> m_Enemies;
    const std::string m_DataPath{ "Data/" };
};

#endif
