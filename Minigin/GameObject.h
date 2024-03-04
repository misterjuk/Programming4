#pragma once
#include <memory>

#include <vector>
#include "Component.h"
#include <stdexcept>

namespace dae
{
    class Texture2D;
    class GameObject final :public std::enable_shared_from_this<GameObject>
    {
    public:
        void Update();
        void Render() const;

        template <typename T, typename... Args>
        void AddComponent(Args&&... args)
        {
            try
            {
                auto ownerWeakPtr = std::weak_ptr<GameObject>(shared_from_this());
                auto component = std::make_unique<T>(ownerWeakPtr, std::forward<Args>(args)...);
                m_Components.emplace_back(std::move(component));
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
                m_Components.erase(
                    std::remove_if(
                        m_Components.begin(),
                        m_Components.end(),
                        [](const auto& component) {
                            return dynamic_cast<T*>(component.get()) != nullptr;
                        }),
                    m_Components.end());
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


        void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition);

        GameObject* GetParent() const { return m_Parent.get(); };

    private:
        std::vector<std::unique_ptr<Component>> m_Components;

        std::shared_ptr<GameObject> m_Parent{ nullptr };
        std::vector<std::shared_ptr<GameObject>> m_Children;

        bool IsChild(std::shared_ptr<GameObject> childToCheck) const;
        void AddChild(std::shared_ptr<GameObject> parent);
        void RemoveChild(std::shared_ptr<GameObject> parent);

        void SetPositionDirty(const bool isPositionDirty);
    };
}