#pragma once
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
    Component() = default;
};