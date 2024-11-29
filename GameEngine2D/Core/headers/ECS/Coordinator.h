#pragma once
#include "SystemManager.h"

namespace GE2D
{
	namespace ECS
	{
		class Coordinator
		{
		    public:
				~Coordinator()
				{

				}
				void Init();

				Entity CreateEntity();
				void DestroyEntity(Entity e);

				/// @brief  Now being handled automatically incase it has not been registered. 
				template <typename T>
				inline ComponentType RegisterComponent()
				{
					return mComponentManager->RegisterCompoent<T>();
				}

				/// @brief When ever a component is added to an array of that component type
	            ///        other parts of the system have to be updated to keep everything running
	            ///        Set the flag of the added component position of the entity to be 1
	            ///        Tell the various system to validate whether or not it quailifies to be handled by that system
	            /// @tparam T Component to add to entity
	            /// @param  e Entity add component to.
				template <typename T>
				inline void AddComponent(Entity e, T component)
				{
					mComponentManager->AddComponent<T>(e, component);

					auto signature = mEntityManager->GetSignature(e);
					signature.set(mComponentManager->GetComponentType<T>(), true);
					mEntityManager->SetSignature(e, signature);

					mSystemManager->OnEntitySignatureUpdate(e, signature);
				}

				template <typename T>
				inline void RemoveComponent(Entity e)
				{
					mComponentManager->RemoveComponent<T>(e);

					auto signature = mEntityManager->GetSignature(e);
					signature.set(mComponentManager->GetComponentType<T>(), false);
					mEntityManager->SetSignature(e, signature);

					mSystemManager->OnEntitySignatureUpdate(e, signature);
				}

				template <typename T>
				inline T& GetCompoenent(Entity e)
				{
					return mComponentManager->GetComponent<T>(e);
				}
		    
				template <typename T>
				inline ComponentType GetCompoenentType()
				{
					return mComponentManager->GetComponentType<T>();
				}

				template <typename T>
				inline std::shared_ptr<T> RegisterSystem()
				{
					return mSystemManager->RegisterSystem<T>();
				}
				
				template <typename T>
				inline void SetSystemSignature(Signature signature)
				{
					mSystemManager->SetSignature<T>(signature);
				}

				template <typename T>
				inline std::shared_ptr<ISystem> GetSystem()
				{
					return mSystemManager->GetSystem<T>();
				}

				template <typename T>
				inline Signature GetSystemSignature()
				{
					return mSystemManager->GetSignature<T>();
				}

				inline void OnUpdate()
				{
					mSystemManager->OnUpdate(this);
				}

				//TEMP: Debug functions
				Signature GetEntitySignature(Entity e)
				{
					return mEntityManager->GetSignature(e);
				}
		     private:
				std::unique_ptr<EntityManager> mEntityManager;
				std::unique_ptr<ComponentManager> mComponentManager;
				std::unique_ptr<SystemManager> mSystemManager;
		};
	}
}
