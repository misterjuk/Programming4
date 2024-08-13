#include "Bullet.h"
#include "EnemyManager.h"
#include "BulletPool.h"

Bullet::Bullet(const glm::vec3& startPosition)
{
	std::unique_ptr<yev::GameObject> bullet = std::make_unique<yev::GameObject>();

	bullet->AddComponent<yev::TransformComponent>(bullet.get());
	bullet->GetComponent<yev::TransformComponent>()->SetLocalPosition(startPosition.x, startPosition.y, 0);
	bullet->AddComponent<yev::RenderComponent>(bullet.get());
	bullet->GetComponent<yev::RenderComponent>()->SetTexture("PLayerBullet.png");
	bullet->AddComponent<BulletComponent>(bullet.get());
	bullet->GetComponent<BulletComponent>()->SetSpeed(200.0f);
	bullet->AddComponent<BulletCollisionComponent>(bullet.get());


	const auto& scene = yev::SceneManager::GetInstance().GetScene("Main");

	m_pBullet = bullet.get();

	scene->Add(std::move(bullet));
}