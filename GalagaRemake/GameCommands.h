#ifndef GAME_COMMANDS_H
#define GAME_COMMANDS_H

#include "Comand.h"
#include "SceneManager.h"
class StartGameCommand : public yev::Command
{
public:
    StartGameCommand() {};

    void Execute() override
    {
        if (yev::SceneManager::GetInstance().GetCurrentSceneName() == "Menu")
        {
            yev::SceneManager::GetInstance().SetScene("Main");
        }   
    }

};
#endif