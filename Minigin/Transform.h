#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class Transform final : public Component
{
public:
	void Update() override;
	void Render(float x = 0.0f, float y = 0.0f) const override;

	const glm::vec3& GetPosition() const { return m_position; }
	void SetPosition(float x, float y, float z);
private:
	glm::vec3 m_position;
};

