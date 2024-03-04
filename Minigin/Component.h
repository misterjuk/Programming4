#pragma once
#include <memory>
namespace dae 
{
    class GameObject;
}
class Component {
public:
    virtual ~Component() {}

    Component(const Component& other) = delete;
    Component(Component&& other) = delete;
    Component& operator=(const Component& other) = delete;
    Component& operator=(Component&& other) = delete;

    virtual void Update() = 0;
    virtual void Render(float x = 0.0f, float y = 0.0f) const = 0;
protected:
    Component(std::weak_ptr<dae::GameObject> owner);
    std::weak_ptr<dae::GameObject> m_Owner;
};