#include "TransformComponent.h"
#include "GameObject.h"

namespace yev {
    TransformComponent::TransformComponent(std::weak_ptr<yev::GameObject> owner) :
        Component(owner)
    {

    }

    void TransformComponent::Update()
    {
    }

  
    void TransformComponent::SetLocalPosition(const glm::vec3& newPosition)
    {
        m_position = newPosition;

        SetPositionDirty(true);
    }
    void TransformComponent::Translate(glm::vec3 const& offset)
    {
        SetLocalPosition(GetLocalPosition() + offset);
    }
    void TransformComponent::SetLocalPosition(const float x, const float y, const float z)
    {
        m_position.x = x;
        m_position.y = y;
        m_position.z = z;

        SetPositionDirty(true);
    }
    glm::vec3 TransformComponent::GetLocalPosition() const
    {
        return m_position;
    }
    glm::vec3 TransformComponent::GetWorldPosition()
    {
        if (m_positionIsDirty)
        {
            UpdateWorldPosition();
        }
        return m_worldPosition;
    }
    void TransformComponent::UpdateWorldPosition()
    {
        if (m_positionIsDirty)
        {
            if (m_Owner.lock().get()->GetParent() == nullptr)
            {
                m_worldPosition = GetLocalPosition();
            }
            else
            {
                m_worldPosition = m_Owner.lock().get()->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition() + GetLocalPosition();
            }
        }
        m_positionIsDirty = false;
    }
    void TransformComponent::SetPositionDirty(const bool isPositionDirty)
    {
        m_positionIsDirty = isPositionDirty;
    }
}
