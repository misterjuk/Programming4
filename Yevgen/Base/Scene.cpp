#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace yev;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(GameObject* object)
{
	m_objects.erase(
		std::remove_if(m_objects.begin(), m_objects.end(),
			[object](const std::unique_ptr<yev::GameObject>& ptr) {
				return ptr.get() == object;
			}),
		m_objects.end());
}


void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		if(object!= nullptr)
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		if(object != nullptr)
		object->Render();
	}
}

