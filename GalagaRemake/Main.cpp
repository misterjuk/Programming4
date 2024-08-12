#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Yevgen.h"
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
#include "BulletPool.h"
#include "HealthComponent.h"

void load()
{
	yev::SceneManager::GetInstance().CreateScene("Demo");
	yev::SceneManager::GetInstance().SetScene("Demo");


	const auto& scene = yev::SceneManager::GetInstance().GetScene("Demo");

	std::unique_ptr<BulletPool> bulletPool = std::make_unique<BulletPool>(100);
	
	auto font = yev::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_unique<yev::GameObject>();
	text->AddComponent<yev::TransformComponent>(text.get());
	text->GetComponent<yev::TransformComponent>()->SetLocalPosition(80, 20, 0);
	text->AddComponent<yev::TextComponent>(text.get(), "Programming 4 Assignment", font);
	scene->Add(std::move(text));

	auto fps = std::make_unique<yev::GameObject>();
	fps->AddComponent<yev::FPSComponent>(fps.get());
	fps->AddComponent<yev::TextComponent>(fps.get(), font);
	fps->AddComponent<yev::TransformComponent>(fps.get());
	fps->GetComponent<yev::TransformComponent>()->SetLocalPosition(20, 430, 0);
	scene->Add(std::move(fps));

	auto character = std::make_unique<yev::GameObject>();
	character->AddComponent<yev::TransformComponent>(character.get());
	character->GetComponent<yev::TransformComponent>()->SetLocalPosition(200, 300, 0);
	character->AddComponent<yev::RenderComponent>(character.get());
	character->GetComponent<yev::RenderComponent>()->SetTexture("Ship.png");

	character->AddComponent<yev::TextComponent>(character.get(), "3", font);
	character->AddComponent<HealthComponent>(character.get());
	
	yev::InputManager& inputManager = yev::InputManager::GetInstance();

	//// Bind WASD keys to character 

	inputManager.BindKeyboardCommand(SDLK_a, yev::InputState::Pressed, std::make_unique<yev::MoveLeftCommand>(character.get()));
	inputManager.BindKeyboardCommand(SDLK_d, yev::InputState::Pressed, std::make_unique<yev::MoveRightCommand>(character.get()));

	inputManager.BindKeyboardCommand(SDLK_e, yev::InputState::Released, std::make_unique<yev::ApplyDamageCommand>(character.get()));
	inputManager.BindKeyboardCommand(SDLK_f, yev::InputState::Pressed, std::make_unique<yev::ShootCommand>(character.get(), bulletPool.get()));

	// Bind D-Pad to control character 
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, yev::InputState::Pressed, std::make_unique<yev::MoveLeftCommand>(character.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, yev::InputState::Pressed, std::make_unique<yev::MoveRightCommand>(character.get()));


	scene->Add(std::move(character));

	
}

int main(int, char*[]) {
	yev::Yevgen engine("../Data/");
	engine.Run(load);
    return 0;
}