#include "Comand.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae {
    class MoveUpCommand : public Command
    {
    public:
        MoveUpCommand(GameObject* character) : m_Character(character) {}

        void Execute() override
        {

            if (m_Character->HasComponent<Transform>())
            {
                m_Character->GetComponent<Transform>()->Translate(glm::vec3(0.0f, -1.0f, 0.0f));
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

            if (m_Character->HasComponent<Transform>())
            {
                m_Character->GetComponent<Transform>()->Translate(glm::vec3(0.0f, 1.0f, 0.0f));
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
            if (m_Character->HasComponent<Transform>())
            {
                m_Character->GetComponent<Transform>()->Translate(glm::vec3(-1.0f, 0.0f, 0.0f));
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
            if (m_Character->HasComponent<Transform>())
            {
                m_Character->GetComponent<Transform>()->Translate(glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }

    private:
       GameObject* m_Character;
    };
}
