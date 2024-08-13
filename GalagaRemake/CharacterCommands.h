#include "Comand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "ServiceLocator.h"
#include "BulletPool.h"
#include "GameEvents.h"

namespace yev {
    class MoveUpCommand : public Command
    {
    public:
        MoveUpCommand(GameObject* character) : m_Character(character) {}

        void Execute() override
        {

            if (m_Character->HasComponent<TransformComponent>())
            {
                m_Character->GetComponent<TransformComponent>()->Translate(glm::vec3(0.0f, -1.0f, 0.0f));
            }
        }

    private:
       GameObject* m_Character;
    };

    class MoveDownCommand : public Command
    {
    public:
        MoveDownCommand(GameObject* character) : m_Character(character) {}

        void Execute() override
        {

            if (m_Character->HasComponent<TransformComponent>())
            {
                m_Character->GetComponent<TransformComponent>()->Translate(glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }

    private:
        GameObject* m_Character;
    };

    class MoveLeftCommand : public Command
    {
    public:
        MoveLeftCommand(GameObject* character) : m_Character(character) {}

        void Execute() override
        {
            if (m_Character->HasComponent<TransformComponent>())
            {
                m_Character->GetComponent<TransformComponent>()->Translate(glm::vec3(-1.0f, 0.0f, 0.0f));
            }
        }

    private:
       GameObject* m_Character;
    };

    class MoveRightCommand : public Command
    {
    public:
        MoveRightCommand(GameObject* character) : m_Character(character) {}

        void Execute() override
        {
            if (m_Character->HasComponent<TransformComponent>())
            {
                m_Character->GetComponent<TransformComponent>()->Translate(glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }

    private:
       GameObject* m_Character;
    };

    class ApplyDamageCommand : public Command
    {
    public:
        ApplyDamageCommand(GameObject* character) : m_Character(character) {}

        void Execute() override
        {
            if (m_Character->HasComponent<HealthComponent>())
            {
                m_Character->GetComponent<HealthComponent>()->Notify(GameEvents::PlayerDamaged, m_Character);
            }

            yev::ServiceLocator::GetInstance().GetSoundSystem()->LoadSoundEffect(0, "Sounds/Shoot.wav", 1, 1);
        }

    private:
        GameObject* m_Character;
    };

    class ShootCommand : public Command
    {
    public:
        ShootCommand(GameObject* character) : m_Character(character) {} 


        void Execute() override
        {
            glm::vec3 position = m_Character->GetComponent<TransformComponent>()->GetWorldPosition();

            BulletPool& pool = BulletPool::GetInstance();
            pool.getBullet(position.x , position.y, 0, -1);

            yev::ServiceLocator::GetInstance().GetSoundSystem()->LoadSoundEffect(0, "Sounds/Shoot.wav", 1, 1);
        }

    private:
        GameObject* m_Character;
    };
}
