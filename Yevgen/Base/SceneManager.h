#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace yev
{
	
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(const std::string& name);
		void SetScene(const std::string& name);
		Scene* GetScene(const std::string& name) const;
		const std::string GetCurrentSceneName() const;


		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<yev::Scene>> m_pScenes;
		yev::Scene* m_CurrentScene;

	};
}
