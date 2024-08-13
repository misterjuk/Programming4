#pragma once


#include "Component.h"

#include "TransformComponent.h"

class BulletComponent :  public yev::Component
{

public:
	BulletComponent(yev::GameObject* owner);
	virtual ~BulletComponent() = default;

	BulletComponent(const BulletComponent& other) = delete;
	BulletComponent(BulletComponent&& other) = delete;
	BulletComponent& operator=(const BulletComponent& other) = delete;
	BulletComponent& operator=(BulletComponent&& other) = delete;

	void SetDirection(const glm::vec3& direction);
	void SetSpeed(float speed);

	void Update() override;
private:

	yev::TransformComponent* m_TransformComponent{nullptr};

	glm::vec3 m_Direction{ (0.0f,0.0,0.0f) };
	float m_Speed{ 1.0f };
};

