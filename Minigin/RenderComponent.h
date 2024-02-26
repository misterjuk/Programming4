#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace dae
{
    class Texture2D;
}

class RenderComponent : public Component
{
public:
    RenderComponent() = default;
    RenderComponent(const std::shared_ptr<dae::Texture2D>& texture);
    virtual ~RenderComponent() = default;

    void Update() override;
    void Render(float x = 0.0f, float y = 0.0f) const override;
    void SetTexture(const std::string& filename);

protected:
    std::shared_ptr<dae::Texture2D> m_texture;
};