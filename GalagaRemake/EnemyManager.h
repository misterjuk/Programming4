#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"
#include <vector>       
#include <fstream>      
#include <sstream>      
#include <string>       
#include <iostream>

class EnemyManager 
{


public:
    EnemyManager() {}

    ~EnemyManager() = default;

    EnemyManager(const EnemyManager& other) = delete;
    EnemyManager& operator=(const EnemyManager& other) = delete;
    EnemyManager(EnemyManager&& other) = delete;
    EnemyManager& operator=(EnemyManager&& other) = delete;

    void LoadEnemiesFromFile(const std::string& filename) 
    {
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

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

            enemies.emplace_back(new Enemy(glm::vec3(x,y,0), type));
        }
        file.close();
    }

   

private:
    std::vector<Enemy*> enemies;
};


#endif