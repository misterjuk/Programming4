#include "BulletPool.h"
#include "GameEvents.h"
void BulletPool::Notify(IObserver::Event event, yev::GameObject* actor)
{


   if (event != GameEvents::EnemyKilled)
       return;

   // Iterate through active bullets to find the matching game object
   for (auto it = activeBullets.begin(); it != activeBullets.end();)
   {
       Bullet* bullet = *it;

       // Check if the bullet's game object matches the actor
      if (bullet->GetGameObject() == actor)
       {
           // Remove the bullet from the active bullets list
           it = activeBullets.erase(it);

           // Return the bullet to the pool
           returnBullet(bullet);
       }
       else
       {
           ++it;
       }
   }




}
