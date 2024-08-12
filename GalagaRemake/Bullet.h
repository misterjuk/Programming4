#ifndef BULLET_H
#define BULLET_H


#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
class Bullet
{

public:



	Bullet(const glm::vec3& startPosition, const glm::vec3& direction)
		:m_Direction{ direction }
	{
		m_pBullet = std::make_unique<yev::GameObject>();
		
		m_pBullet->AddComponent<yev::TransformComponent>(m_pBullet.get());
		m_pBullet->GetComponent<yev::TransformComponent>()->SetLocalPosition(startPosition.x, startPosition.y, 0);
		m_pBullet->AddComponent<yev::RenderComponent>(m_pBullet.get());
		m_pBullet->GetComponent<yev::RenderComponent>()->SetTexture("Ship.png");
	}

	Bullet()
		: Bullet( glm::vec3(0,0,0) , glm::vec3(0,0,0))
	{

	}

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
		m_Direction = direction;
	}

	void Move()
	{
		//glm::vec3 offset
		m_pBullet->GetComponent<yev::TransformComponent>()->Translate(m_Direction);
	}

private:
	std::unique_ptr<yev::GameObject> m_pBullet;


	glm::vec3 m_Direction;
};

#endif