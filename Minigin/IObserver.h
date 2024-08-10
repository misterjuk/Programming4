#pragma once

namespace dae
{
	enum class Event
	{
		PlayerDied,
		PlayerDamaged,
		PlayerScored,
		EnemyKilled,
		LevelCompleted
		
	};

	class GameObject;

	class IObserver
	{
		public:
			virtual ~IObserver() = default;
			virtual void Notify(Event event, GameObject* actor) = 0;
	};
}


