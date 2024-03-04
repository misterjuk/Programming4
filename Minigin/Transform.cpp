#include "Transform.h"
#include "GameObject.h"

Transform::Transform(std::weak_ptr<dae::GameObject> owner):
    Component(owner)
{

}

void Transform::Update()
{
}

void Transform::Render(float x, float y) const
{
	x = 0.0f;
	y = 0.0f;
}
void Transform::SetLocalPosition(const glm::vec3& newPosition)
{
    m_position = newPosition;

    SetPositionDirty(true);
}
void Transform::SetLocalPosition(const float x, const float y, const float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    SetPositionDirty(true);
}
glm::vec3 Transform::GetLocalPosition() const
{
    return m_position;
}
glm::vec3 Transform::GetWorldPosition()
{
    if (m_positionIsDirty)
    {
        UpdateWorldPosition();
    }
    return m_worldPosition;
}
void Transform::UpdateWorldPosition()
{
    if (m_positionIsDirty)
    {
        if (m_Owner.lock()->GetParent() == nullptr)
        {
            m_worldPosition = GetLocalPosition();
        }
        else
        {
            m_worldPosition = m_Owner.lock()->GetParent()->GetComponent<Transform>()->GetWorldPosition() + GetLocalPosition();
        }
    }
    m_positionIsDirty = false;
}
void Transform::SetPositionDirty(const bool isPositionDirty) 
{
    m_positionIsDirty = isPositionDirty;
}