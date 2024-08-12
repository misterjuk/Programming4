#include "Component.h"
#include <memory>
#include "GameObject.h"

namespace yev {
	Component::Component(GameObject* owner)
	{
		m_Owner = owner;
	}

}
