#pragma once
#include "IObserver.h"
#include <vector>

namespace dae
{
    class Subject
    {
    public:
        void AddObserver(IObserver* observer)
        {
            m_Observers.push_back(observer);
        }

        void RemoveObserver(IObserver* observer)
        {
            m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
        }

        void NotifyObservers(Event event, GameObject* actor)
        {
            for (IObserver* observer : m_Observers)
            {
                observer->Notify(event, actor);
            }
        }

    private:
        std::vector<IObserver*> m_Observers;
    };
}
