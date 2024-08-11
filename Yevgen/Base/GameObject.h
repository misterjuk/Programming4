#pragma once


#include <vector>
#include "Component.h"
#include <stdexcept>
#include <memory>

namespace yev
{
    class GameObject final
    {
    public:
        void Update();
        void Render() const;

        template <typename T, typename... Args>
        void AddComponent(Args&&... args)
        {
            try
            {
                m_Components.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            }
            catch (const std::exception& e)
            {
                // Handle exception: log the error, rethrow with a custom message, or take appropriate action.
                throw std::runtime_error("AddComponent failed: " + std::string(e.what()));
            }
        }

        template <typename T>
        void RemoveComponent()
        {
            try
            {           
                auto end = std::remove_if(
                    m_Components.begin(),
                    m_Components.end(),
                    [](const auto& component) {
                        // Check if the component is of type T
                        return dynamic_cast<T*>(component.get()) != nullptr;
                    });
            
                m_Components.erase(end, m_Components.end());
            }
            catch (const std::exception& e)
            {
                // Handle exception: log the error, rethrow with a custom message, or take appropriate action.
                throw std::runtime_error("RemoveComponent failed: " + std::string(e.what()));
            }
        }

        template <typename T>
        T* GetComponent() const
        {
            try
            {
                for (const auto& component : m_Components)
                {
                    if (auto castedComponent = dynamic_cast<T*>(component.get()))
                        return castedComponent;
                }
                return nullptr;
            }
            catch (const std::exception& e)
            {
                // Handle exception: log the error, rethrow with a custom message, or take appropriate action.
                throw std::runtime_error("GetComponent failed: " + std::string(e.what()));
            }
        }

        template <typename T>
        bool HasComponent() const
        {
            try
            {
                for (const auto& component : m_Components)
                {
                    if (dynamic_cast<T*>(component.get()) != nullptr)
                        return true;
                }
                return false;
            }
            catch (const std::exception& e)
            {
                // Handle exception: log the error, rethrow with a custom message, or take appropriate action.
                throw std::runtime_error("HasComponent failed: " + std::string(e.what()));
            }
        }

        GameObject() = default;
        ~GameObject();
        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;


        void SetParent(GameObject* parent, bool keepWorldPosition);

        GameObject* GetParent() const { return m_Parent; };

    private:
        std::vector<std::unique_ptr<Component>> m_Components;

        GameObject* m_Parent;

        std::vector<std::unique_ptr<GameObject>> m_Children;

        bool IsChild(GameObject* childToCheck) const;
        void AddChild(GameObject* child);
        void RemoveChild(GameObject* child);

        void SetPositionDirty(const bool isPositionDirty);
    };
}