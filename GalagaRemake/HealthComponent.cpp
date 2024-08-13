#include "HealthComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "GameEvents.h"

HealthComponent::HealthComponent(yev::GameObject* owner, yev::TextComponent* textComponent)
	:Component(owner)
{

	m_pHealthText = textComponent;
}



void HealthComponent::Notify(IObserver::Event event, yev::GameObject*)
	{
		if (event == GameEvents::PlayerDamaged)
		{
			--m_Health;

			m_pHealthText->SetText(std::to_string(m_Health));

			if (m_Health <= 0)
			{
				yev::SceneManager::GetInstance().SetScene("EndScreen");
			}
		}
		
	}


