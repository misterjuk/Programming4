#pragma once

#include "GameObject.h"
#include "Component.h"


class ScoreComponent final : public yev::Component
{

	ScoreComponent(yev::GameObject* ownerObjectPtr);
	~ScoreComponent() = default;

	ScoreComponent(ScoreComponent const&) = delete;
	ScoreComponent(ScoreComponent&&) = delete;
	ScoreComponent& operator=(ScoreComponent const&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) = delete;


};

