#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(std::weak_ptr<yev::GameObject> owner)
	:Component(owner)
{
	if (owner.lock().get()->HasComponent<yev::TextComponent>())
	{
		m_pHealthText = owner.lock().get()->GetComponent<yev::TextComponent>();
	}
}



void HealthComponent::Notify(yev::Event event, yev::GameObject*)
	{
		if (event == yev::Event::PlayerDamaged)
		{
			--m_Health;

			m_pHealthText->SetText(std::to_string(m_Health));
		}
		
	}


