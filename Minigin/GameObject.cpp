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
//void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
//{
//    if (IsChild(parent) || parent == this || m_parent == parent)
//        return;
//    if (parent == nullptr)
//        SetLocalPosition(GetWorldPosition());
//    else
//    {
//        if (keepWorldPosition)
//            SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
//        SetPositionDirty()
//            if (m_parent) m_parent->RemoveChild(this);
//        m_parent = parent;
//        if (m_parent) m_parent->AddChild(this)
//    }
//}

