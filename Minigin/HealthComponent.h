#pragma once


#include "IObserver.h"
#include "Component.h"
#include "TextComponent.h"

#include "TextComponent.h"
	class HealthComponent final : public dae::IObserver , public dae::Component
	{
	public:


		HealthComponent(std::weak_ptr<dae::GameObject> owner);
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;
		

		


		void Notify(dae::Event event, dae::GameObject* actor) override;
	private:

		int m_Health{ 3 };


		dae::TextComponent* m_pHealthText;
	};



