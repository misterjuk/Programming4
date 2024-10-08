#pragma once
#include "Component.h"
#include <memory>
#include <string>


namespace yev
{
    class Texture2D;

    class TransformComponent;

    class RenderComponent : public Component
    {
    public:
        RenderComponent(GameObject* owner);
        RenderComponent(GameObject* owner, const std::shared_ptr<yev::Texture2D>& texture);
        virtual ~RenderComponent() = default;

        void Update() override;
        void Render() const override;
        void SetTexture(const std::string& filename);

    protected:
        //load texture returns the shared ptr, so probablt no need for uniqueptr
        std::shared_ptr<yev::Texture2D> m_texture;
        
        TransformComponent* m_Transform;
    };
}

