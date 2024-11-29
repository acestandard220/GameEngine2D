#include "Entity.h"
namespace GE2D
{
	namespace ECS
	{

		EntityManager::EntityManager()
		{
			nIDUse = 0;
			for (uint32_t i = 0; i < MAX_ENTITIES_SUPPORTED; i++)
			{
				mAvailableIDS.push(i);
			}
		}

		Entity EntityManager::CreateEntity()
		{
			GAME_ENGINE_2D_ASSERT(nIDUse < MAX_ENTITIES_SUPPORTED && "Maximum Entity capacity reached");

			Entity id = mAvailableIDS.front();
			mAvailableIDS.pop();

			nIDUse++;
			return id;
		}

		bool EntityManager::DestroyEntity(Entity e)
		{
			GAME_ENGINE_2D_ASSERT(e < MAX_ENTITIES_SUPPORTED && "Cannot perform operation invalid Entity");

			mSignatures[e].reset();

			mAvailableIDS.push(e);
			nIDUse--;
			return true;
		}




		bool EntityManager::SetSignature(Entity e, Signature signature)
		{
			GAME_ENGINE_2D_ASSERT(e < MAX_ENTITIES_SUPPORTED && "Cannot perform operation invalid Entity");

			mSignatures[e] = signature;
			return true;
		}


		Signature EntityManager::GetSignature(Entity e)
		{
			GAME_ENGINE_2D_ASSERT(e < MAX_ENTITIES_SUPPORTED && "Cannot perform operation invalid Entity");

			auto signature = mSignatures[e];

			return signature;
		}


	}
}
