#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update() 
{
    for (const auto& component : m_Components)
    {
        component->Update();
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_Components)
    {
        if (HasComponent<Transform>())
        {
            const auto transform = GetComponent<Transform>();
           
            component->Render(transform->GetPosition().x, transform->GetPosition().y);
        }
        else 
        {
            component->Render();
        }
        
    }
}


