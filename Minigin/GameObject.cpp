#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

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
       component->Render();      
   }
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_Parent == parent)
    {
        return;
    }
    if (parent == nullptr)
    {
        if (m_Parent)
        {
            m_Parent->RemoveChild(this);
        }

        m_Parent = nullptr;

        GetComponent<TransformComponent>()->SetLocalPosition(GetComponent<TransformComponent>()->GetWorldPosition());
    }
    else
    {
        if (keepWorldPosition)
        {
            GetComponent<TransformComponent>()->SetLocalPosition(GetComponent<TransformComponent>()->GetWorldPosition() - parent->GetComponent<TransformComponent>()->GetWorldPosition());
        }

        SetPositionDirty(true);

        if (m_Parent)
        {
           
            m_Parent->RemoveChild(this);
        }

        m_Parent = parent;

        if (m_Parent)
        {
           
            m_Parent->AddChild(this);
        }
    }
}

bool dae::GameObject::IsChild(GameObject* childToCheck) const
{
    for (const auto& child : m_Children)
    {
        if (child.get() == childToCheck || child->IsChild(childToCheck))
        {
            return true;
        }
    }
    return false;
}

void dae::GameObject::AddChild(GameObject* child)
{
    // Add the child to the vector of children

    //TODO GIVES MEMORY LEAKS
     m_Children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
    m_Children.erase(
        std::remove_if(
            m_Children.begin(),
            m_Children.end(),
            [child = std::move(child)](const std::unique_ptr<GameObject>& ptr) { return ptr.get() == child; }
        ),
        m_Children.end()
    );
}
void dae::GameObject::SetPositionDirty(const bool isPositionDirty) 
{
    //TOOD Set childs dirty
    GetComponent<TransformComponent>()->SetPositionDirty(isPositionDirty);

    for (const auto& child : m_Children)
    {
        child->SetPositionDirty(isPositionDirty);
    }
}