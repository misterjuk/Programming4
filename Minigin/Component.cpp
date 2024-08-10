#include "Component.h"
#include <memory>
#include "GameObject.h"

namespace dae {
	Component::Component(std::weak_ptr<dae::GameObject> owner)
	{
		m_Owner = owner;
	}

}
