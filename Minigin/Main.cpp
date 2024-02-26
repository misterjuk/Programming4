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
#include "Transform.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	go->AddComponent<Transform>();
	go->GetComponent<Transform>()->SetPosition(216, 180, 0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->AddComponent<Transform>();
	go->GetComponent<Transform>()->SetPosition(80, 20, 0);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<FPSComponent>(go);
	go->AddComponent<TextComponent>(font);
	go->AddComponent<Transform>();
	go->GetComponent<Transform>()->SetPosition(20, 430, 0);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}