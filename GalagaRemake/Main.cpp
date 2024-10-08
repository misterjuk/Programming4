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
#include "ScoreComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "InputManager.h"

#include "CharacterCommands.h"
#include "GameCommands.h"

#include "windows.h"
#include "XInput.h"
#include "BulletPool.h"
#include "HealthComponent.h"

#include "EnemyManager.h"

void load()
{
	auto font = yev::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	yev::InputManager& inputManager = yev::InputManager::GetInstance();

	yev::SceneManager::GetInstance().CreateScene("Menu");	
	yev::SceneManager::GetInstance().CreateScene("Main");
	yev::SceneManager::GetInstance().CreateScene("EndScreen");



	yev::SceneManager::GetInstance().SetScene("Menu");

	const auto& menuScene = yev::SceneManager::GetInstance().GetScene("Menu");

	auto title = std::make_unique<yev::GameObject>();
	title->AddComponent<yev::TransformComponent>(title.get());
	title->GetComponent<yev::TransformComponent>()->SetLocalPosition(250, 150, 0);
	title->AddComponent<yev::TextComponent>(title.get(), "Galaga", font);
	menuScene->Add(std::move(title));

	auto desciption = std::make_unique<yev::GameObject>();
	desciption->AddComponent<yev::TransformComponent>(desciption.get());
	desciption->GetComponent<yev::TransformComponent>()->SetLocalPosition(150, 250, 0);
	desciption->AddComponent<yev::TextComponent>(desciption.get(), "Press X to Start", font);
	menuScene->Add(std::move(desciption));

	auto controls = std::make_unique<yev::GameObject>();
	controls->AddComponent<yev::TransformComponent>(controls.get());
	controls->GetComponent<yev::TransformComponent>()->SetLocalPosition(100, 350, 0);
	controls->AddComponent<yev::TextComponent>(controls.get(), "F - Shoot, A,D - Move", font);
	menuScene->Add(std::move(controls));

	auto controllercontrols = std::make_unique<yev::GameObject>();
	controllercontrols->AddComponent<yev::TransformComponent>(controllercontrols.get());
	controllercontrols->GetComponent<yev::TransformComponent>()->SetLocalPosition(50, 400, 0);
	controllercontrols->AddComponent<yev::TextComponent>(controllercontrols.get(), "Y - Shoot, DPAD left/right - Move", font);
	menuScene->Add(std::move(controllercontrols));

	
	inputManager.BindKeyboardCommand(SDLK_x, yev::InputState::Pressed, std::make_unique<StartGameCommand>());
	


	const auto& scene = yev::SceneManager::GetInstance().GetScene("Main");


	EnemyManager::GetInstance().LoadEnemiesFromFile("EnemyFormations/Level1.txt");

	BulletPool::GetInstance().InitializeBulletPool();
	

	/*auto score = std::make_unique<yev::GameObject>();
	score->AddComponent<yev::TransformComponent>(score.get());
	score->GetComponent<yev::TransformComponent>()->SetLocalPosition(250, 50, 0);
	score->AddComponent<yev::TextComponent>(score.get(), font);
	scene->Add(std::move(score));*/

	auto fps = std::make_unique<yev::GameObject>();
	fps->AddComponent<yev::FPSComponent>(fps.get());
	fps->AddComponent<yev::TextComponent>(fps.get(), font);
	fps->AddComponent<yev::TransformComponent>(fps.get());
	fps->GetComponent<yev::TransformComponent>()->SetLocalPosition(20, 430, 0);
	scene->Add(std::move(fps));

	auto healthCounter = std::make_unique<yev::GameObject>();
	healthCounter->AddComponent<yev::TransformComponent>(healthCounter.get());
	healthCounter->GetComponent<yev::TransformComponent>()->SetLocalPosition(20, 430, 0);
	healthCounter->AddComponent<yev::TextComponent>(healthCounter.get(), "3", font);
	


	auto character = std::make_unique<yev::GameObject>();
	character->AddComponent<yev::TransformComponent>(character.get());
	character->GetComponent<yev::TransformComponent>()->SetLocalPosition(200, 400, 0);
	character->AddComponent<yev::RenderComponent>(character.get());
	character->GetComponent<yev::RenderComponent>()->SetTexture("Ship.png");
	character->AddComponent<HealthComponent>(character.get(), healthCounter->GetComponent<yev::TextComponent>());
	
	

	//// Bind WASD keys to character 

	inputManager.BindKeyboardCommand(SDLK_a, yev::InputState::Held, std::make_unique<yev::MoveLeftCommand>(character.get()));
	inputManager.BindKeyboardCommand(SDLK_d, yev::InputState::Held, std::make_unique<yev::MoveRightCommand>(character.get()));

	inputManager.BindKeyboardCommand(SDLK_F1, yev::InputState::Released, std::make_unique<yev::ApplyDamageCommand>(character.get()));

	inputManager.BindControllerCommand(XINPUT_GAMEPAD_Y, yev::InputState::Pressed, std::make_unique<yev::ShootCommand>(character.get()));
	inputManager.BindKeyboardCommand(SDLK_f, yev::InputState::Pressed, std::make_unique<yev::ShootCommand>(character.get()));

	// Bind D-Pad to control character 
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, yev::InputState::Held, std::make_unique<yev::MoveLeftCommand>(character.get()));
	inputManager.BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, yev::InputState::Held, std::make_unique<yev::MoveRightCommand>(character.get()));

	inputManager.BindControllerCommand(XINPUT_GAMEPAD_X, yev::InputState::Pressed, std::make_unique<StartGameCommand>());

	scene->Add(std::move(character));

	scene->Add(std::move(healthCounter));

	const auto& endScene = yev::SceneManager::GetInstance().GetScene("EndScreen");

	auto highscore = std::make_unique<yev::GameObject>();
	highscore->AddComponent<yev::TransformComponent>(highscore.get());
	highscore->GetComponent<yev::TransformComponent>()->SetLocalPosition(250, 150, 0);
	highscore->AddComponent<yev::TextComponent>(highscore.get(), "HighScore", font);
	highscore->AddComponent<ScoreComponent>(highscore.get());
	endScene->Add(std::move(highscore));
}

int main(int, char*[]) {
	yev::Yevgen engine("Data/");
	engine.Run(load);
    return 0;
}