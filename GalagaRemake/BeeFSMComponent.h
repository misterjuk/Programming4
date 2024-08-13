#ifndef BEE_FSM_COMPONENT_H
#define BEE_FSM_COMPONENT_H

#include "GameObject.h"
#include "Component.h"
#include <cmath> // For std::sin and M_PI
#include <glm/glm.hpp>

class BeeFSMComponent : public yev::Component
{
public:
    BeeFSMComponent(yev::GameObject* owner);
    virtual ~BeeFSMComponent() = default;

    BeeFSMComponent(const BeeFSMComponent& other) = delete;
    BeeFSMComponent& operator=(const BeeFSMComponent& other) = delete;
    BeeFSMComponent(BeeFSMComponent&& other) = delete;
    BeeFSMComponent& operator=(BeeFSMComponent&& other) = delete;

    void Update() override; // Called every frame to update the component

private:
    enum class State
    {
        MovingLeftRight,
        MovingUpDown
    };

    State m_currentState;
    float m_time; // To track the sine wave progress
    float m_amplitude; // Amplitude of the sine wave
    float m_frequency; // Frequency of the sine wave

    void UpdateMovement();
    void SwitchState(State newState);
};

#endif // BEE_FSM_COMPONENT_H