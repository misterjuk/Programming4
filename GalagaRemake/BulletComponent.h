#pragma once


#include "Component.h"

#include "TransformComponent.h"

class BulletComponent :  public yev::Component
{


	BulletComponent(yev::GameObject* owner);
	virtual ~BulletComponent() = default;

	BulletComponent(const BulletComponent& other) = delete;
	BulletComponent(BulletComponent&& other) = delete;
	BulletComponent& operator=(const BulletComponent& other) = delete;
	BulletComponent& operator=(BulletComponent&& other) = delete;


	void Update() override;
private:

	yev::TransformComponent* m_TransformComponent{nullptr};
};

