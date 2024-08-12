#include "InputManager.h"
#include "Controller.h"
#include <SDL.h>
#include <algorithm>

namespace yev
{
    InputManager::InputManager()
        : m_Controller(std::make_unique<Controller>())
    {
    }

    InputManager::~InputManager() = default;

    bool InputManager::ProcessInput()
    {
        SDL_Event e;
        std::unordered_map<SDL_Keycode, bool> currentKeyStates;

        // Initialize key states for the frame
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        for (const auto& [key, commandPair] : m_KeyboardCommands)
        {
            currentKeyStates[key] = keyboardState[SDL_GetScancodeFromKey(key)] != 0;
        }

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                return false;

            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                SDL_Keycode key = e.key.keysym.sym;
                bool keyIsPressed = (e.type == SDL_KEYDOWN);
                currentKeyStates[key] = keyIsPressed;
            }
        }

        // Process keyboard commands based on the current key states
        for (const auto& [key, commandPair] : m_KeyboardCommands)
        {
            const auto& [state, command] = commandPair;
            bool keyIsPressed = currentKeyStates[key];

            if ((state == InputState::Pressed && keyIsPressed) ||
                (state == InputState::Released && !keyIsPressed && IsPressed(key)) ||
                (state == InputState::Held && keyIsPressed))
            {
                command->Execute();
            }
        }

        // Update and process controller input
        m_Controller->Update();

        return true;
    }

    void InputManager::BindKeyboardCommand(SDL_Keycode key, InputState state, std::unique_ptr<Command> command)
    {
        m_KeyboardCommands[key] = std::make_pair(state, std::move(command));

       
    }

    void InputManager::BindControllerCommand(unsigned int button, InputState state, std::unique_ptr<Command> command)
    {
        m_Controller->BindControllerCommand(button, state, std::move(command));
    }

    bool InputManager::IsPressed(SDL_Keycode key)
    {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        return state[SDL_GetScancodeFromKey(key)] != 0;
    }
}