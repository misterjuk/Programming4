#include "EnemyManager.h"
#include "SceneManager.h"
#include "GameEvents.h"
void EnemyManager::Notify(IObserver::Event event, yev::GameObject* actor)
{
    if (event != GameEvents::EnemyKilled)
        return;

    // Iterate through the enemies vector
    for (auto it = m_Enemies.begin(); it != m_Enemies.end(); /* no increment here */)
    {
        // Compare the GameObject of each enemy with the provided actor
        if ((*it)->GetGameObject() == actor)
        {
            const auto& scene = yev::SceneManager::GetInstance().GetScene("Main");
            scene->Remove((*it)->GetGameObject());

            // Properly delete the enemy object if necessary
            delete* it; // Assuming m_Enemies contains raw pointers

            // Remove the enemy from the vector
            it = m_Enemies.erase(it);
        }
        else
        {
            ++it; // Only increment the iterator if we didn't erase the current element
        }
    }
}


