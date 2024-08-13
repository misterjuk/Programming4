#include "BeeFSMComponent.h"
#include "TransformComponent.h"
#include "GameTime.h"

BeeFSMComponent::BeeFSMComponent(yev::GameObject* owner)
    : yev::Component(owner), m_currentState(State::MovingLeftRight), m_time(0.0f), m_amplitude(40.0f), m_frequency(1.5)
{
}

void BeeFSMComponent::Update()
{
    m_time += GameTime::GetInstance().GetDeltaTime();

    // Update movement based on the current state
    UpdateMovement();

    // Switch state based on time
    if (m_time > 1) // For example, switch state every 5 seconds
    {
        SwitchState(m_currentState == State::MovingLeftRight ? State::MovingUpDown : State::MovingLeftRight);
        // Reset time after switching state
        m_time = -1.0f;
    }
}

void BeeFSMComponent::UpdateMovement()
{
    float movement = m_amplitude * std::sin(m_frequency * m_time) * GameTime::GetInstance().GetDeltaTime();

    auto transform = m_Owner->GetComponent<yev::TransformComponent>();

    switch (m_currentState)
    {
    case State::MovingLeftRight:
        // Move left and right relative to the initial position
        transform->Translate(glm::vec3(movement,0.0f,0.0f));
        break;

    case State::MovingUpDown:
        // Move up and down relative to the initial position
        transform->Translate(glm::vec3(0.0, movement, 0.0f));
        break;
    }
}

void BeeFSMComponent::SwitchState(State newState)
{
    m_currentState = newState;
    m_time = 0.0f; // Reset time when switching states

}



