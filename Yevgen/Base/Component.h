#pragma once
#include <memory>
namespace yev 
{
    class GameObject;

    class Component {
    public:
        virtual ~Component() = default;
        Component(GameObject* owner);

        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;


        virtual void Update() {};
        virtual void Render() const {};
        
    protected:
        
        
            
        GameObject* m_Owner;
    };
}
