#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace yev {
	class RotatorComponent final : public Component
	{
	public:

		RotatorComponent(GameObject* owner);
		~RotatorComponent() = default;

		void Update() override;

		void SetRadius(const float radius) { m_Radius = radius; };
		void SetSpeed(const float speed) { m_Speed = speed; };
		// Update function to be called in the game loop


	private:
		// Member variables
		float m_Radius{};  // Rotation radius
		float m_Speed{};   // Rotation speed

		float m_Angle{};

		glm::vec3 m_TargetPosition{};
	};

}

