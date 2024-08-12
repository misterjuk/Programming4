#include "Controller.h"


namespace yev
{
    Controller::Controller()
    {
        ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
    }

    Controller::~Controller() = default;

    void Controller::Update()
    {
        ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
        XInputGetState(0, &m_ControllerState);

        for (const auto& [button, commandPair] : m_ControllerCommands)
        {
            const auto& [state, command] = commandPair;
            bool isPressed = IsPressed(button);

            if ((state == InputState::Pressed && isPressed) ||
                (state == InputState::Released && !isPressed) ||
                (state == InputState::Held && isPressed))
            {
                command->Execute();
            }
        }   
    }

    void Controller::BindControllerCommand(unsigned int button, InputState state, std::unique_ptr<Command> command)
    {
        m_ControllerCommands[button] = std::make_pair(state, std::move(command));
    }
        
    bool Controller::IsPressed(unsigned int button)
    {
        return (m_ControllerState.Gamepad.wButtons & button) != 0;
    }
}