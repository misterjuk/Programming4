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
    RenderComponent(std::weak_ptr<dae::GameObject> owner);
    RenderComponent(std::weak_ptr<dae::GameObject> owner ,const std::shared_ptr<dae::Texture2D>& texture);
    virtual ~RenderComponent() = default;

    void Update() override;
    void Render(float x = 0.0f, float y = 0.0f) const override;
    void SetTexture(const std::string& filename);

protected:
    //load texture returns the shared ptr, so probablt no need for uniqueptr
    std::shared_ptr<dae::Texture2D> m_texture;
};