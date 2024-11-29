#pragma once
#include "Entity.h"
#include "../core.h"

namespace GE2D
{
	namespace ECS
	{
		using ComponentType = uint32_t;

		class IComponentArray
		{
		public:
			virtual ~IComponentArray() = default;
			virtual void OnEntityDestroy(Entity e) = 0;
		};

		template <typename T>
		class ComponentArray : public IComponentArray
		{
		public:
			ComponentArray()
			{
				mNextIndex = 0;
			}
			inline void AddEntity(Entity e, T component)
			{
				GAME_ENGINE_2D_ASSERT(mEntity_Index.find(e) == mEntity_Index.end() && "Entity already has the component");

				uint32_t newIndex = mNextIndex;
				mEntity_Index[e] = mNextIndex;
				mIndex_Entity[newIndex] = e;

				mComponents[newIndex] = component;

				mNextIndex++;
			}
			inline void RemoveEntity(Entity e)
			{
				GAME_ENGINE_2D_ASSERT(mEntity_Index.find(e) != mEntity_Index.end() && "Entity does not have this component");

				uint32_t indexRemove = mEntity_Index[e];
				uint32_t indexLast = mNextIndex - 1;
				mComponents[indexRemove] = mComponents[indexLast];

				Entity entityLast = mIndex_Entity[indexLast];
				mEntity_Index[entityLast] = indexRemove;
				mIndex_Entity[indexRemove] = entityLast;

				mEntity_Index.erase(e);
				mIndex_Entity.erase(indexLast);

				mNextIndex--;
			}

			inline T& GetComponent(Entity e)
			{
				GAME_ENGINE_2D_ASSERT(mEntity_Index.find(e) != mEntity_Index.end() && "Entity does not have this component");

				uint32_t actualIndex = mEntity_Index[e];

				return mComponents[actualIndex];
			}
			inline virtual void OnEntityDestroy(Entity e) override
			{
				if (mEntity_Index.find(e) != mEntity_Index.end())
				{
					RemoveEntity(e);
				}
				//TODO: Implementation............
			}



		private:

			uMapping<uint32_t, Entity> mIndex_Entity;
			uMapping<Entity, uint32_t> mEntity_Index;

			std::array<T, MAX_ENTITIES_SUPPORTED> mComponents;

			uint32_t mNextIndex;
		};


		class ComponentManager
		{
		public:
			ComponentManager();

			template <typename T>
			inline ComponentType RegisterCompoent()
			{
				const char* name = typeid(T).name();
				GAME_ENGINE_2D_ASSERT(mComponentArrays.find(name) == mComponentArrays.end() && "Component has already been registered");

				mComponentArrays.insert({ name, std::make_shared<ComponentArray<T>>() });
				mComponentTypes.insert({ name, mNextCompTypeSignature });

				return mNextCompTypeSignature++;
			}

			template <typename T>
			inline void AddComponent(Entity e, T& component)
			{
				const char* name = typeid(T).name();
				if (mComponentArrays.find(name) == mComponentArrays.end())
				{
					RegisterCompoent<T>();
				}
				GAME_ENGINE_2D_ASSERT(mComponentArrays.find(name) != mComponentArrays.end() && "Component has not been registered");

				GetComponentArray<T>()->AddEntity(e, component);
			}


			template <typename T>
			inline void RemoveComponent(Entity e)
			{
				const char* name = typeid(T).name();
				GAME_ENGINE_2D_ASSERT(mComponentArrays.find(name) != mComponentArrays.end() && "Component has not been registered");

				GetComponentArray<T>()->RemoveEntity(e);
			}

			template <typename T>
			inline T& GetComponent(Entity e)
			{
				const char* name = typeid(T).name();
				GAME_ENGINE_2D_ASSERT(mComponentArrays.find(name) != mComponentArrays.end() && "Component has not been registered");

				return GetComponentArray<T>()->GetComponent(e);
			}

			template <typename T>
			inline ComponentType GetComponentType()
			{
				const char* name = typeid(T).name();
				return mComponentTypes[name];
			}



			void OnEntityDestroyed(Entity e);
		private:
			template <typename T>
			std::shared_ptr<ComponentArray<T>> GetComponentArray()
			{
				const char* name = typeid(T).name();
				GAME_ENGINE_2D_ASSERT(mComponentArrays.find(name) != mComponentArrays.end() && "Component has not been registered");

				return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[name]);
			}

		private:
			uMapping<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
			uMapping<const char*, ComponentType> mComponentTypes;

			ComponentType mNextCompTypeSignature;
		};
	}
}

