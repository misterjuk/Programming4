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
#include "Transform.h"
#include "Scene.h"
#include "InputManager.h"
#include "CharacterCommands.h"
#include "windows.h"
#include "XInput.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>(go);
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>(go);
	go->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	go->AddComponent<Transform>(go);
	go->GetComponent<Transform>()->SetLocalPosition(216, 180, 0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>(go,"Programming 4 Assignment", font);
	go->AddComponent<Transform>(go);
	go->GetComponent<Transform>()->SetLocalPosition(80, 20, 0);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<FPSComponent>(go);
	go->AddComponent<TextComponent>(go,font);
	go->AddComponent<Transform>(go);
	go->GetComponent<Transform>()->SetLocalPosition(20, 430, 0);
	scene.Add(go);

	auto parent = std::make_shared<dae::GameObject>();
	parent->AddComponent<RenderComponent>(parent);
	parent->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	parent->AddComponent<Transform>(parent);
	parent->GetComponent<Transform>()->SetLocalPosition(200, 300, 0);
	
	scene.Add(parent);

	dae::InputManager& inputManager = dae::InputManager::GetInstance();

	//// Bind WASD keys to character 1
	inputManager.BindKeyboardCommand(SDLK_w, dae::InputState::Pressed, std::make_shared<dae::MoveUpCommand>(parent.get()));
	inputManager.BindKeyboardCommand(SDLK_s, dae::InputState::Pressed, std::make_shared<dae::MoveDownCommand>(parent.get()));
	inputManager.BindKeyboardCommand(SDLK_a, dae::InputState::Pressed, std::make_shared<dae::MoveLeftCommand>(parent.get()));
	inputManager.BindKeyboardCommand(SDLK_d, dae::InputState::Pressed, std::make_shared<dae::MoveRightCommand>(parent.get()));

	// Bind D-Pad to control gameObject2 (using double speed, as an example)
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, dae::InputState::Pressed, std::make_shared<dae::MoveUpCommand>(parent.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputState::Pressed, std::make_shared<dae::MoveDownCommand>(parent.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputState::Pressed, std::make_shared<dae::MoveLeftCommand>(parent.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputState::Pressed, std::make_shared<dae::MoveRightCommand>(parent.get()));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}