#pragma once
#include "GameObject.h"
namespace yev
{
	class GameObject;
	class Scene final
	{

		//scenemanger needs to include the scene, so i cannnot include scenemanager there and make a friend, so i am making the constructor public
		//friend void yev::SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);


		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string GetName() { return m_name; }

	private: 
		

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}
