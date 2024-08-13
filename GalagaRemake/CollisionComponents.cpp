#include "CollisionComponents.h"

#include "EnemyManager.h"
#include "BulletPool.h"
#include "GameEvents.h"
CollisionComponent::CollisionComponent(yev::GameObject* owner, Tag tag):
	Component(owner), m_Tag{tag}
{
	m_Transform = owner->GetComponent<yev::TransformComponent>();
}

bool CollisionComponent::CheckCollision(const glm::vec4& otherCollider) {
    if (m_Transform == nullptr) {
        // TransformComponent must be set
        return false;
    }

    // Get the world position and size of the current collider
    glm::vec3 position = m_Transform->GetWorldPosition();
    glm::vec4 thisCollider(position.x, position.y, m_Collider.z, m_Collider.w);

    // Check for AABB collision
    return (thisCollider.x < otherCollider.x + otherCollider.z &&
        thisCollider.x + thisCollider.z > otherCollider.x &&
        thisCollider.y < otherCollider.y + otherCollider.w &&
        thisCollider.y + thisCollider.w > otherCollider.y);
}

BulletCollisionComponent::BulletCollisionComponent(yev::GameObject* owner)
    :CollisionComponent(owner ,Tag::Bullet)
{
}

void BulletCollisionComponent::Update()
{
    // Get the vector of enemies from the EnemyManager
    auto& enemies = EnemyManager::GetInstance().GetEnemies();

    // Iterate through the vector of enemies
    for (Enemy* enemy : enemies)
    {
        // Get the enemy's collider
        glm::vec4 enemyCollider = enemy->GetGameObject()->GetComponent<EnemyCollisionComponent>()->GetCollider();

        // Check for a collision between the bullet and the enemy
        if (CheckCollision(enemyCollider))
        {
           
            EnemyManager::GetInstance().Notify(GameEvents::EnemyKilled, enemy->GetGameObject());
            BulletPool::GetInstance().Notify(GameEvents::EnemyKilled, m_Owner);

            break;
        }
    }
}

EnemyCollisionComponent::EnemyCollisionComponent(yev::GameObject* owner)
    :CollisionComponent(owner, Tag::Enemy)
{
}
