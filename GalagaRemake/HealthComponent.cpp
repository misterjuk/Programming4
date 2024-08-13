#include "HealthComponent.h"
#include "GameObject.h"
#include "SceneManager.h"

HealthComponent::HealthComponent(yev::GameObject* owner)
	:Component(owner)
{
	if (owner->HasComponent<yev::TextComponent>())
	{
		m_pHealthText = owner->GetComponent<yev::TextComponent>();
	}
}



void HealthComponent::Notify(yev::Event event, yev::GameObject*)
	{
		if (event == yev::Event::PlayerDamaged)
		{
			--m_Health;

			m_pHealthText->SetText(std::to_string(m_Health));

			if (m_Health <= 0)
			{
				yev::SceneManager::GetInstance().SetScene("EndScreen");
			}
		}
		
	}


