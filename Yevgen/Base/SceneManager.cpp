#include "SceneManager.h"
#include "Scene.h"

void yev::SceneManager::Update()
{	
		m_CurrentScene->Update();
}

void yev::SceneManager::Render()
{
	m_CurrentScene->Render();
}

void yev::SceneManager::CreateScene(const std::string& name)
{
	m_pScenes.push_back(std::make_unique<Scene>(name));
}

void yev::SceneManager::SetScene(const std::string& name)
{
	m_CurrentScene = GetScene(name);
}

yev::Scene* yev::SceneManager::GetScene(const std::string& name) const
{
	for (const auto& scene : m_pScenes)
	{
		if (scene->GetName() == name)
		{
			return scene.get();
		}
	}

	return nullptr; 
}

const std::string yev::SceneManager::GetCurrentSceneName() const
{
	return m_CurrentScene->GetName();
}
