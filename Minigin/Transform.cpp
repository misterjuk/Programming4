#include "Transform.h"

void Transform::Update()
{
}

void Transform::Render(float x, float y) const
{
	x = 0.0f;
	y = 0.0f;
}

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
