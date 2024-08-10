#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(std::weak_ptr<dae::GameObject> owner)
	:Component(owner)
{
	if (owner.lock().get()->HasComponent<dae::TextComponent>())
	{
		m_pHealthText = owner.lock().get()->GetComponent<dae::TextComponent>();
	}
}



void HealthComponent::Notify(dae::Event event, dae::GameObject*)
	{
		if (event == dae::Event::PlayerDamaged)
		{
			--m_Health;

			m_pHealthText->SetText(std::to_string(m_Health));
		}
		
	}


