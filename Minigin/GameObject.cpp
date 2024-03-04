#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

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
          
           component->Render(transform->GetWorldPosition().x, transform->GetWorldPosition().y);
       }
       else 
       {
           component->Render();
       }
       
   }
}
void dae::GameObject::SetParent(std::shared_ptr<dae::GameObject> parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent.get() == this || m_Parent == parent)
    {
        return;
    }
    if (parent == nullptr)
    {
        GetComponent<Transform>()->SetLocalPosition(GetComponent<Transform>()->GetWorldPosition());
    }
    else
    {
        if (keepWorldPosition)
        {
            GetComponent<Transform>()->SetLocalPosition(GetComponent<Transform>()->GetLocalPosition() - parent->GetComponent<Transform>()->GetWorldPosition());
        }

        SetPositionDirty(true);

        if (m_Parent)
        {
            m_Parent->RemoveChild(shared_from_this());
        }

        m_Parent = parent;

        if (m_Parent) 
        {
            m_Parent->AddChild(shared_from_this());
        }
    }
}
bool dae::GameObject::IsChild(std::shared_ptr<GameObject> childToCheck) const
{
    for (const auto& child : m_Children)
    {
        if (child == childToCheck || child->IsChild(childToCheck))
        {
            return true;
        }
    }
    return false;
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
    // Add the child to the vector of children

    //TODO GIVES MEMORY LEAKS
     m_Children.emplace_back(child);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
    m_Children.erase(
        std::remove_if(
            m_Children.begin(),
            m_Children.end(),
            [child](const std::shared_ptr<GameObject>& ptr) { return ptr == child; }
        ),
        m_Children.end()
    );
}
void dae::GameObject::SetPositionDirty(const bool isPositionDirty) 
{
    GetComponent<Transform>()->SetPositionDirty(isPositionDirty);
}