#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "GameObject.h"

RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner)
    : Component(owner), m_texture(nullptr)
{
}

RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner, const std::shared_ptr<dae::Texture2D>& texture)
    : Component(owner), m_texture(texture)
{
}


void RenderComponent::Update()
{
}

void RenderComponent::Render(float x, float y) const
{
    if (m_texture != nullptr)
    {
        dae::Renderer::GetInstance().RenderTexture(*m_texture, x, y);
    }
}

void RenderComponent::SetTexture(const std::string& filename)
{
    m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}