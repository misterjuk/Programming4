#pragma once


#include "IObserver.h"
#include "Component.h"
#include "TextComponent.h"

#include "GameObject.h"
	class HealthComponent final : public yev::IObserver , public yev::Component
	{
	public:


		HealthComponent(yev::GameObject* owner);
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;
		

		


		void Notify(yev::Event event, yev::GameObject* actor) override;
	private:

		int m_Health{ 3 };


		yev::TextComponent* m_pHealthText;
	};



