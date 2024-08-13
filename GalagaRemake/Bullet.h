#ifndef BULLET_H
#define BULLET_H


#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "BulletComponent.h"
#include <iostream>
class Bullet
{

public:



	Bullet(const glm::vec3& startPosition)	
	{
		std::unique_ptr<yev::GameObject> bullet = std::make_unique<yev::GameObject>();
		
		bullet->AddComponent<yev::TransformComponent>(bullet.get());
		bullet->GetComponent<yev::TransformComponent>()->SetLocalPosition(startPosition.x, startPosition.y, 0);
		bullet->AddComponent<yev::RenderComponent>(bullet.get());
		bullet->GetComponent<yev::RenderComponent>()->SetTexture("PLayerBullet.png");
		bullet->AddComponent<BulletComponent>(bullet.get());

		const auto& scene = yev::SceneManager::GetInstance().GetScene("Main");

		m_pBullet = bullet.get();

		scene->Add(std::move(bullet));
	}

	Bullet()
		: Bullet( glm::vec3(0,0,0))
	{}

	// Destructor
	~Bullet() = default;

	Bullet(const Bullet& other) = delete;
	Bullet& operator=(const Bullet& other) = delete;
	Bullet(Bullet&& other) = delete;
	Bullet& operator=(Bullet&& other) = delete;

	void SetPosition(const glm::vec3& position) 
	{
		std::cout << "Position set to:" + std::to_string(position.x) + "," + std::to_string(position.y);
		m_pBullet->GetComponent<yev::TransformComponent>()->SetLocalPosition(position.x, position.y, 0);
	}
	void SetDirection(const glm::vec3& direction)
	{
		m_pBullet->GetComponent<BulletComponent>()->SetDirection(direction);
		m_pBullet->GetComponent<BulletComponent>()->SetSpeed(5);
	}


private:
	yev::GameObject* m_pBullet;


};

#endif