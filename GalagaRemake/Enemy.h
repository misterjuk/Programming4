#ifndef ENEMY_H
#define ENEMY_H


#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include <iostream>
class Enemy
{

public:

	Enemy(const glm::vec3& startPosition)
	{
		std::unique_ptr<yev::GameObject> enemy = std::make_unique<yev::GameObject>();

		enemy->AddComponent<yev::TransformComponent>(enemy.get());
		enemy->GetComponent<yev::TransformComponent>()->SetLocalPosition(startPosition.x, startPosition.y, 0);
		enemy->AddComponent<yev::RenderComponent>(enemy.get());
		enemy->GetComponent<yev::RenderComponent>()->SetTexture("PLayerBullet.png");

		const auto& scene = yev::SceneManager::GetInstance().GetScene("Main");

		m_pEnemy = enemy.get();

		scene->Add(std::move(enemy));
	}

	Enemy()
		: Enemy(glm::vec3(0, 0, 0))
	{}

	// Destructor
	~Enemy() = default;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;


private:
	yev::GameObject* m_pEnemy;
};

#endif