#include "RotatorComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameTime.h"

RotatorComponent::RotatorComponent(std::weak_ptr<dae::GameObject> owner)
    : Component(owner)
{
    m_TargetPosition = owner.lock().get()->GetComponent<Transform>()->GetWorldPosition();
}

void RotatorComponent::Update()
{
    if (m_Owner.lock().get() == nullptr)
        return;

    auto transform = m_Owner.lock().get()->GetComponent<Transform>();

    //TODO Should cap it, will run into issue when its too large;
    m_Angle += m_Speed * GameTime::GetInstance().GetDeltaTime();

    glm::vec3 position;

    position.x = m_TargetPosition.x + m_Radius * std::cos(m_Angle);
    position.y = m_TargetPosition.y + m_Radius * std::sin(m_Angle);
    transform->SetLocalPosition(position);
}

void RotatorComponent::Render(float x, float y) const
{
    x = 0.0f;
    y = 0.0f;
}
