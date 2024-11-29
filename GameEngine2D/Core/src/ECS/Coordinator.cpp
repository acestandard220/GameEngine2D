#include "Coordinator.h"

namespace GE2D
{
	namespace ECS
	{
		void Coordinator::Init()
		{
			mEntityManager = std::make_unique<EntityManager>();
			mComponentManager = std::make_unique<ComponentManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}

		Entity Coordinator::CreateEntity()
		{
			return mEntityManager->CreateEntity();
		}

		void Coordinator::DestroyEntity(Entity e)
		{
			mEntityManager->DestroyEntity(e);
			mComponentManager->OnEntityDestroyed(e);
			mSystemManager->OnEntityDestroued(e);
		}
		
	}

}