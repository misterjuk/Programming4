#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include "Bullet.h"
#include "glm/glm.hpp"

class BulletPool
{
public:
    // Constructor
    BulletPool(std::size_t size)
    {
        // Pre-allocate bullets and store them in the pool
        for (std::size_t i = 0; i < size; ++i)
        {
            bullets.emplace_back(std::make_unique<Bullet>());
            availableBullets.push(bullets.back().get());
        }
    }

    // Destructor
    ~BulletPool() = default;

    BulletPool(const BulletPool& other) = delete;
    BulletPool& operator=(const BulletPool& other) = delete;
    BulletPool(BulletPool&& other) = delete;
    BulletPool& operator=(BulletPool&& other) = delete;

    // Get a bullet from the pool, set its initial position and direction
    std::unique_ptr<Bullet> getBullet(int startX, int startY, int dx, int dy)
    {
        if (availableBullets.empty())
        {
            return nullptr; // Handle by resizing the pool if dynamic resizing is desired
        }

        // Get a bullet from the pool
        Bullet* bullet = availableBullets.front();
        availableBullets.pop();

        // Set the initial position and direction for the bullet
        bullet->SetPosition(glm::vec3(startX, startY, 0));
        bullet->SetDirection(glm::vec3(dx, dy, 0));

        // Track this bullet as active
        activeBullets.emplace_back(bullet);

        // Create a unique_ptr for the bullet to return
        return std::unique_ptr<Bullet>(bullet);
    }

    // Return a bullet to the pool
    void returnBullet(std::unique_ptr<Bullet> bullet)
    {
        // Remove from active bullets
        auto it = std::remove(activeBullets.begin(), activeBullets.end(), bullet.get());
        activeBullets.erase(it, activeBullets.end());

        // Add the bullet back to the pool
        availableBullets.push(bullet.release());
    }



private:
    std::vector<std::unique_ptr<Bullet>> bullets;      // Storage for all bullets
    std::queue<Bullet*> availableBullets;              // Queue to manage available bullets
    std::vector<Bullet*> activeBullets;                // Track currently active bullets
};

#endif // BULLET_POOL_H
