#pragma once
class Component {
public:
    Component() = default;
    virtual ~Component() {}

    Component(const Component& other) = delete;
    Component(Component&& other) = delete;
    Component& operator=(const Component& other) = delete;
    Component& operator=(Component&& other) = delete;

    virtual void Update() = 0;
};