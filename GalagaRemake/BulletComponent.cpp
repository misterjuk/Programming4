#include "BulletComponent.h"
#include "GameObject.h"


BulletComponent::BulletComponent(yev::GameObject* owner)
	:Component(owner)
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
	
	m_TransformComponent->Translate(m_Direction * m_Speed);
}
