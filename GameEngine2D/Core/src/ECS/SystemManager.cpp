#include "SystemManager.h"
namespace GE2D
{
	namespace ECS
	{

		
		/// @brief For every system this manager has we would like to erase the destroyed entity
		/// @param e Destroyed entity
		void SystemManager::OnEntityDestroued(Entity e)
		{
			for (auto& const pair : mSystems)
			{
				auto& const system = pair.second;
				system->enitites.erase(e);
			}
		}

		/// @brief Called when the siganture of an entitied changes
		///        Called to check whether or not the entity still needs to be handles by that system
		/// @param e Entity with changed signature
		/// @param signature Signature to compare with systems required siganture
		void SystemManager::OnEntitySignatureUpdate(Entity e, Signature eSignature)
		{
			for (auto& pair : mSystems)
			{
				auto& const name = pair.first;
				auto& const system = pair.second;
				auto& const signature = mSignatures[name];

				if ((signature & eSignature) == signature)
				{
					system->enitites.insert(e);
				}
				else
				{
					system->enitites.erase(e);
				}
			}

		}
	}
}
