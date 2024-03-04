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
	go->GetComponent<Transform>()->SetLocalPosition(216, 180, 0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->AddComponent<Transform>();
	go->GetComponent<Transform>()->SetLocalPosition(80, 20, 0);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<FPSComponent>();
	go->AddComponent<TextComponent>(font);
	go->AddComponent<Transform>();
	go->GetComponent<Transform>()->SetLocalPosition(20, 430, 0);
	scene.Add(go);

	auto parent = std::make_shared<dae::GameObject>();
	parent->AddComponent<RenderComponent>();
	parent->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	parent->AddComponent<Transform>();
	parent->GetComponent<Transform>()->SetLocalPosition(200, 300, 0);
	parent->AddComponent<RotatorComponent>();
	parent->GetComponent<RotatorComponent>()->SetRadius(100.0f);
	parent->GetComponent<RotatorComponent>()->SetSpeed(2.0f);
	scene.Add(parent);

	auto child = std::make_shared<dae::GameObject>();
	child->AddComponent<RenderComponent>();
	child->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	child->AddComponent<Transform>();
	child->GetComponent<Transform>()->SetLocalPosition(0, 0, 0);
	child->AddComponent<RotatorComponent>();
	child->GetComponent<RotatorComponent>()->SetRadius(100.0f);
	child->GetComponent<RotatorComponent>()->SetSpeed(5.0f);
	child->SetParent(parent, false);
	scene.Add(child);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}