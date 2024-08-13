#include "BulletComponent.h"
#include "GameObject.h"
#include "GameTime.h"

BulletComponent::BulletComponent(yev::GameObject* owner)
	:Component(owner), m_Speed{200.f}
{

	m_TransformComponent = owner->GetComponent<yev::TransformComponent>();
}

void BulletComponent::SetDirection(const glm::vec3& direction)
{

	m_Direction = direction;
}

void BulletComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void BulletComponent::Update()
{
	glm::vec3 offset = m_Direction * m_Speed * GameTime::GetInstance().GetDeltaTime();
	m_TransformComponent->Translate(offset);
}
