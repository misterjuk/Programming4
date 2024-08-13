#pragma once

namespace yev
{
	
	class GameObject;

	class IObserver
	{



		public:
			virtual ~IObserver() = default;

			using Event = int;
			virtual void Notify(Event event, GameObject* actor) = 0;
	};
}


