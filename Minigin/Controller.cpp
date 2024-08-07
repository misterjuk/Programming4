#include "Controller.h"


namespace dae
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
            auto [state, command] = commandPair;
            bool isPressed = IsPressed(button);

            if ((state == InputState::Pressed && isPressed) ||
                (state == InputState::Released && !isPressed) ||
                (state == InputState::Held && isPressed))
            {
                command->Execute();
            }
        }
    }

    void Controller::BindControllerCommand(unsigned int button, InputState state, std::shared_ptr<Command> command)
    {
        m_ControllerCommands[button] = std::make_pair(state, command);
    }

    bool Controller::IsPressed(unsigned int button)
    {
        return (m_ControllerState.Gamepad.wButtons & button) != 0;
    }
}