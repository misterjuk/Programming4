#ifndef BULLET_H
#define BULLET_H


#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "BulletComponent.h"
#include <iostream>
#include "CollisionComponents.h"
#include "Enemy.h"

class Bullet final
{

public:



	Bullet(const glm::vec3& startPosition);

	Bullet()
		: Bullet(glm::vec3(0,-20,0))
	{}

	// Destructor
	~Bullet() = default;

	Bullet(const Bullet& other) = delete;
	Bullet& operator=(const Bullet& other) = delete;
	Bullet(Bullet&& other) = delete;
	Bullet& operator=(Bullet&& other) = delete;

	void SetPosition(const glm::vec3& position) 
	{
		m_pBullet->GetComponent<yev::TransformComponent>()->SetLocalPosition(position.x, position.y, 0);
	}
	void SetDirection(const glm::vec3& direction)
	{
		m_pBullet->GetComponent<BulletComponent>()->SetDirection(direction);
		m_pBullet->GetComponent<BulletComponent>()->SetSpeed(400.0f);
	}

	yev::GameObject* GetGameObject() const { return m_pBullet; }
private:
	yev::GameObject* m_pBullet;


};

#endif