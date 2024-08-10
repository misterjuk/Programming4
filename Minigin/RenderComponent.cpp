#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae {
    RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner)
        : Component(owner), m_texture(nullptr)
    {      

        //todo call another constructor
        m_Transform = owner.lock().get()->GetComponent<TransformComponent>();       
    }

    RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner, const std::shared_ptr<dae::Texture2D>& texture)
        : Component(owner), m_texture(texture)
    {
        m_Transform = owner.lock().get()->GetComponent<TransformComponent>();
    }


    void RenderComponent::Update()
    {
    }

    void RenderComponent::Render() const
    {
        if (m_texture != nullptr)
        {
            if (m_Transform != nullptr)
            {
                dae::Renderer::GetInstance().RenderTexture(*m_texture, m_Transform->GetWorldPosition().x, m_Transform->GetWorldPosition().y);
            }
            else 
            {
                dae::Renderer::GetInstance().RenderTexture(*m_texture, 0, 0);
            }
        }
    }

    void RenderComponent::SetTexture(const std::string& filename)
    {
        m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
    }
}
