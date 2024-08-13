#ifndef ENEMY_H
#define ENEMY_H


#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include <iostream>
#include "CollisionComponents.h"

enum class EnemyType {
	Bee,
	Butterfly,
	Boss
};

class Enemy final
{

public:

	Enemy(const glm::vec3& startPosition, EnemyType type)
		: m_Type{type}
	{
		std::unique_ptr<yev::GameObject> enemy = std::make_unique<yev::GameObject>();

		enemy->AddComponent<yev::TransformComponent>(enemy.get());
		enemy->GetComponent<yev::TransformComponent>()->SetLocalPosition(startPosition.x, startPosition.y, 0);
		enemy->AddComponent<yev::RenderComponent>(enemy.get());
		enemy->AddComponent<EnemyCollisionComponent>(enemy.get());
		switch (type)
		{
		case EnemyType::Bee:
			enemy->GetComponent<yev::RenderComponent>()->SetTexture("Bee.png");
			break;
		case EnemyType::Butterfly:
			enemy->GetComponent<yev::RenderComponent>()->SetTexture("Butterfly.png");
			break;
		case EnemyType::Boss:
			enemy->GetComponent<yev::RenderComponent>()->SetTexture("Boss.png");
			break;
		default:
			break;
		}
		

		const auto& scene = yev::SceneManager::GetInstance().GetScene("Main");

		m_pEnemy = enemy.get();

		scene->Add(std::move(enemy));
	}

	Enemy()
		: Enemy(glm::vec3(0, 0, 0), EnemyType::Bee)
	{}

	// Destructor
	~Enemy() = default;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;


	yev::GameObject* GetGameObject() const{ return m_pEnemy; }
private:
	yev::GameObject* m_pEnemy{nullptr};

	EnemyType m_Type{ EnemyType::Bee };
};

#endif