#include "ComponentArray.h"

namespace GE2D
{
    namespace ECS
    {

        ComponentManager::ComponentManager()
        {
            mNextCompTypeSignature = 0;
        }

        void ComponentManager::OnEntityDestroyed(Entity e)
        {
            for (auto& pair : mComponentArrays)
            {
                auto& component = pair.second;
                component->OnEntityDestroy(e);
            }
            //TODO: Implementation.............
        }
    }
}
