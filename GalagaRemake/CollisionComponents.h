#ifndef COLLISION_COMPONENTS_H
#define COLLISION_COMPONENTS_H

#include "GameObject.h"
#include "TransformComponent.h"

#include "Subject.h"
class CollisionComponent : public yev::Component, public yev::Subject
{

public:

	enum class Tag
	{
		None,
		Player,
		Enemy,
		Bullet
	};

	CollisionComponent(yev::GameObject* owner, Tag tag = Tag::None);
	virtual ~CollisionComponent() = default;

	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) = delete;

	bool CheckCollision(const glm::vec4& otherCollider);

	glm::vec4 GetCollider(float posX, float posY) const { return glm::vec4(posX,posY, m_ColliderDimensions.z, m_ColliderDimensions.w); }
private:
	glm::vec4 m_ColliderDimensions{ (0.0f,0.0f,20.0f,20.0f) };
	yev::TransformComponent* m_Transform{};
	Tag m_Tag{ Tag::None };
};

class BulletCollisionComponent final : public CollisionComponent
{

public:
	BulletCollisionComponent(yev::GameObject* owner);
	virtual ~BulletCollisionComponent() = default;

	BulletCollisionComponent(const BulletCollisionComponent& other) = delete;
	BulletCollisionComponent(BulletCollisionComponent&& other) = delete;
	BulletCollisionComponent& operator=(const BulletCollisionComponent& other) = delete;
	BulletCollisionComponent& operator=(BulletCollisionComponent&& other) = delete;

	void Update() override;

private:


};

class EnemyCollisionComponent final : public CollisionComponent
{

public:
	EnemyCollisionComponent(yev::GameObject* owner);
	virtual ~EnemyCollisionComponent() = default;

	EnemyCollisionComponent(const EnemyCollisionComponent& other) = delete;
	EnemyCollisionComponent(EnemyCollisionComponent&& other) = delete;
	EnemyCollisionComponent& operator=(const EnemyCollisionComponent& other) = delete;
	EnemyCollisionComponent& operator=(EnemyCollisionComponent&& other) = delete;

	

private:


};

#endif