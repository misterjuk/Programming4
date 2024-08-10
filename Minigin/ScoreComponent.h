#pragma once

#include "GameObject.h"
#include "Component.h"


class ScoreComponent final : public dae::Component
{

	ScoreComponent(dae::GameObject* ownerObjectPtr);
	~ScoreComponent() = default;

	ScoreComponent(ScoreComponent const&) = delete;
	ScoreComponent(ScoreComponent&&) = delete;
	ScoreComponent& operator=(ScoreComponent const&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) = delete;


};

