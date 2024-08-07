#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include <memory>

namespace dae
{
	class GameObject;
}
class Transform final : public Component
{
public:

	Transform(std::weak_ptr<dae::GameObject> owner);

	void Update() override;
	void Render(float x = 0.0f, float y = 0.0f) const override;

	void SetLocalPosition(const float x, const float y, const float z);
	void SetLocalPosition(const glm::vec3& newPosition);

	void Translate(glm::vec3 const& offset);


	glm::vec3 GetLocalPosition() const;

	glm::vec3 GetWorldPosition();
	
	void UpdateWorldPosition();

	void SetPositionDirty(const bool isPositionDirty);
private:

	bool m_positionIsDirty{ true };

	glm::vec3 m_position{};

	glm::vec3 m_worldPosition{};
};

