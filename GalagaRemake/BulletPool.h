#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include <vector>
#include <queue>
#include <algorithm>
#include "Bullet.h"
#include "glm/glm.hpp"
#include "Singleton.h" // Include the Singleton template

class BulletPool : public yev::Singleton<BulletPool>
{
    // Allow Singleton to access private members
    friend class yev::Singleton<BulletPool>;

public:
    // Delete copy constructor and assignment operators
    BulletPool(const BulletPool& other) = delete;
    BulletPool& operator=(const BulletPool& other) = delete;
    BulletPool(BulletPool&& other) = delete;
    BulletPool& operator=(BulletPool&& other) = delete;

    // Initialize the bullet pool with a specific size
    void InitializeBulletPool(int size = 100)
    {
        // Pre-allocate bullets and store them in the pool
        bullets.reserve(size);
        for (int i = 0; i < size; ++i)
        {
            Bullet* bullet = new Bullet();
            availableBullets.push(bullet);
            bullets.push_back(bullet);
        }
    }

    // Get a bullet from the pool, set its initial position and direction
    Bullet* getBullet(int startX, int startY, int dx, int dy)
    {
        if (availableBullets.empty())
        {
            // Optional: Handle dynamic resizing here if needed
            return nullptr; // Handle by resizing the pool if needed
        }

        // Get a bullet from the pool
        Bullet* bullet = availableBullets.front();
        availableBullets.pop();

        if (bullet)
        {
            // Set the initial position and direction for the bullet
            bullet->SetPosition(glm::vec3(startX, startY, 0));
            bullet->SetDirection(glm::vec3(dx, dy, 0));

            // Track this bullet as active
            activeBullets.push_back(bullet);

            return bullet;
        }

        return nullptr; // Handle null pointer case if needed
    }

    // Return a bullet to the pool
    void returnBullet(Bullet* bullet)
    {
        if (bullet)
        {
            // Remove from active bullets
            auto it = std::remove(activeBullets.begin(), activeBullets.end(), bullet);
            activeBullets.erase(it, activeBullets.end());

            // Add the bullet back to the pool
            availableBullets.push(bullet);
        }
    }

private:
    BulletPool() = default; // Private constructor
    ~BulletPool()
    {
        // Clean up all allocated bullets
        for (Bullet* bullet : bullets)
        {
            delete bullet;
        }
    }

    std::vector<Bullet*> bullets;          // Storage for all bullets
    std::queue<Bullet*> availableBullets;  // Queue to manage available bullets
    std::vector<Bullet*> activeBullets;    // Track currently active bullets
};

#endif // BULLET_POOL_H
