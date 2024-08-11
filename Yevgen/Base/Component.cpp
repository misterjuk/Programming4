#include "Component.h"
#include <memory>
#include "GameObject.h"

namespace yev {
	Component::Component(std::weak_ptr<yev::GameObject> owner)
	{
		m_Owner = owner;
	}

}
