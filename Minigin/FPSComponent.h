#pragma once
#include <chrono>
#include "Component.h"
#include <string>


namespace dae 
{
    class GameObject;

    class FPSComponent final : public Component
    {
    public:
        FPSComponent(std::weak_ptr<dae::GameObject> owner);
        ~FPSComponent() = default;


        void Update() override;
      

    protected:
        float m_TimeBetweenUpdates = 0.07f; // seconds
        std::chrono::steady_clock::time_point m_lastUpdateTime;
        std::string m_text;
    };
}

