#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

RenderComponent::RenderComponent(const std::shared_ptr<dae::Texture2D>& texture)
    : Component(), m_texture(texture)
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