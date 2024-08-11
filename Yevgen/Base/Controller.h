#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "windows.h"
#include <XInput.h>
#include <unordered_map>
#include <memory>
#include "Comand.h"
#include "InputManager.h"

namespace yev
{
    class Controller
    {
    public:
        Controller();
        ~Controller();

        void Update();
        void BindControllerCommand(unsigned int button, InputState state, std::shared_ptr<Command> command);

    private:
        std::unordered_map<unsigned int, std::pair<InputState, std::shared_ptr<Command>>> m_ControllerCommands;
        XINPUT_STATE m_ControllerState{};
        bool IsPressed(unsigned int button);
    };
}

#endif // CONTROLLER_H