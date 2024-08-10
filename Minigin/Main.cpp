#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "InputManager.h"
#include "CharacterCommands.h"
#include "windows.h"
#include "XInput.h"

#include "HealthComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>(go);
	go->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	scene.Add(go);

	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TransformComponent>(go);
	go->GetComponent<dae::TransformComponent>()->SetLocalPosition(80, 20, 0);
	go->AddComponent<dae::TextComponent>(go, "Programming 4 Assignment", font);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::FPSComponent>(go);
	go->AddComponent<dae::TextComponent>(go,font);
	go->AddComponent<dae::TransformComponent>(go);
	go->GetComponent<dae::TransformComponent>()->SetLocalPosition(20, 430, 0);
	scene.Add(go);

	auto character = std::make_shared<dae::GameObject>();
	character->AddComponent<dae::TransformComponent>(character);
	character->GetComponent<dae::TransformComponent>()->SetLocalPosition(200, 300, 0);
	character->AddComponent<dae::RenderComponent>(character);
	character->GetComponent<dae::RenderComponent>()->SetTexture("logo.tga");

	character->AddComponent<dae::TextComponent>(character, "3", font);
	character->AddComponent<HealthComponent>(character);
	
	scene.Add(character);

	dae::InputManager& inputManager = dae::InputManager::GetInstance();

	//// Bind WASD keys to character 1
	
	inputManager.BindKeyboardCommand(SDLK_a, dae::InputState::Pressed, std::make_shared<dae::MoveLeftCommand>(character.get()));
	inputManager.BindKeyboardCommand(SDLK_d, dae::InputState::Pressed, std::make_shared<dae::MoveRightCommand>(character.get()));

	inputManager.BindKeyboardCommand(SDLK_e, dae::InputState::Pressed, std::make_shared<dae::ApplyDamageCommand>(character.get()));

	// Bind D-Pad to control gameObject2 (using double speed, as an example)
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, dae::InputState::Pressed, std::make_shared<dae::MoveUpCommand>(character.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputState::Pressed, std::make_shared<dae::MoveDownCommand>(character.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputState::Pressed, std::make_shared<dae::MoveLeftCommand>(character.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputState::Pressed, std::make_shared<dae::MoveRightCommand>(character.get()));


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}