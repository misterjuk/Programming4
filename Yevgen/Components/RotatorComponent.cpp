#include "RotatorComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameTime.h"

namespace yev {
    RotatorComponent::RotatorComponent(GameObject* owner)
        : Component(owner)
    {
        m_TargetPosition = owner->GetComponent<TransformComponent>()->GetWorldPosition();
    }

    void RotatorComponent::Update()
    {
        if (m_Owner == nullptr)
            return;

        auto transform = m_Owner->GetComponent<TransformComponent>();

        //TODO Should cap it, will run into issue when its too large;
        m_Angle += m_Speed * GameTime::GetInstance().GetDeltaTime();

        glm::vec3 position;

        position.x = m_TargetPosition.x + m_Radius * std::cos(m_Angle);
        position.y = m_TargetPosition.y + m_Radius * std::sin(m_Angle);
        transform->SetLocalPosition(position);
    }

  

}
