#include "ECS/Coordinator.h"
#include "ECS/Components.h"

namespace GE2D
{
	namespace ECS
	{
		void Coordinator::Init()
		{
			spatial_partition = std::make_unique<QuadTree>(0, glm::vec3(-10.0f, -10.0f, 0.0f), glm::vec2(20.0f,20.0f), * this);

			mEntityManager = std::make_unique<EntityManager>();
			mComponentManager = std::make_unique<ComponentManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}

		Entity Coordinator::CreateEntity()
		{
			Entity temp = mEntityManager->CreateEntity();

			///@brief default component that get added
			TransformComponent tc = {
				{0.0f,0.0f,0.0f}, //Position
				{0.10f,0.10f,0.10f}, //Scale
				{0.0f,0.0f,0.0f}  //Rotation
			};

			TagComponent tag = {
				{"GameObject_DEFAULTY_ PSIAL"}
			};

			///@brief add components by default
			AddComponent<TransformComponent>(temp,tc);
			AddComponent<TagComponent>(temp, tag);
			return temp;
		}

		void Coordinator::DestroyEntity(Entity e)
		{
			mEntityManager->DestroyEntity(e);
			mComponentManager->OnEntityDestroyed(e);
			mSystemManager->OnEntityDestroued(e);
		}

		QuadTree::QuadTree(int level, glm::vec3 position, glm::vec2 size, Coordinator& coord)
			:bounds(position, size), coordinator(coord), level(level)
		{

		}

		QuadTree::~QuadTree()
		{
			delete northEast;
			delete northWest;
			delete southEast;
			delete southWest;

			mEntities.clear();
		}

		void QuadTree::Insert(Entity e)
		{
			if (northEast)
			{
				auto quads = GetQuads(e);
				for (auto quad : quads)
				{
					quad->Insert(e);
				}
				return;
			}

			mEntities.push_back(e);

			if (mEntities.size() > MAX_PER_QUAD && level < MAX_LEVEL)
			{
				Split();
				for (auto& ent : mEntities)
				{
					Insert(e);
				}
				mEntities.clear();
			}
		}

		void QuadTree::Split()
		{
			glm::vec3 new_position = bounds.position;
			glm::vec2 new_size = glm::vec2(bounds.size.x / 2, bounds.size.y / 2);

			northEast = new QuadTree(level + 1, { new_position.x + new_size.x,new_position.y + new_size.y,new_position.z }, new_size, coordinator);
			northWest = new QuadTree(level + 1, { new_position.x, new_position.y + new_size.y,new_position.z }, new_size, coordinator);

			southEast = new QuadTree(level + 1, { new_position.x + new_size.x,new_position.y,new_position.z }, new_size, coordinator);
			southWest = new QuadTree(level + 1, new_position, new_size, coordinator);
		}

		std::vector<QuadTree*> QuadTree::GetQuads(Entity e)
		{

			std::vector<QuadTree*> returnQuards;
			auto& component = coordinator.GetCompoenent<TransformComponent>(e);
			glm::vec3 _position = component.Position;
			glm::vec3 _size = component.Scale;

			if (northEast->bounds.Contains(_position, { _size.x,_size.y }))
			{
				returnQuards.push_back(northEast);
			}
			if (northWest->bounds.Contains(_position, { _size.x,_size.y }))
			{
				returnQuards.push_back(northWest);
			}
			if (southEast->bounds.Contains(_position, { _size.x,_size.y }))
			{
				returnQuards.push_back(southEast);
			}
			if (southWest->bounds.Contains(_position, { _size.x,_size.y }))
			{
				returnQuards.push_back(southWest);
			}

			return returnQuards;
		}

		bool QuadTree::Remove(Entity e)
		{
			if (northEast)
			{
				if (northEast->Remove(e))
					return true;
				if (northWest->Remove(e))
					return true;
				if (southEast->Remove(e))
					return true;
				if (southWest - Remove(e))
					return true;
			}

			auto& component = coordinator.GetCompoenent<TransformComponent>(e);
			glm::vec3 _position = component.Position;
			glm::vec3 _size = component.Scale;

			if (this->bounds.Contains(_position, _size))
			{
				auto it = std::find(mEntities.begin(), mEntities.end(), e);
				mEntities.erase(it);
				return true;
			}

			return false;
		}

		void QuadTree::Clear()
		{
			delete northEast;
			delete northWest;
			delete southEast;
			delete southWest;

			mEntities.clear();
		}

		std::vector<Entity> QuadTree::GetFriendEntities(Entity e)
		{
			std::vector<Entity> friends;

			if (northEast)
			{
				auto ne = northEast->GetFriendEntities(e);
				if (!ne.empty())
					return ne;
				auto nw = northWest->GetFriendEntities(e);
				if (!nw.empty())
					return nw;
				auto se = southEast->GetFriendEntities(e);
				if (!se.empty())
					return se;
				auto sw = southWest->GetFriendEntities(e);
				if (!sw.empty())
					return sw;
			}

			auto& component = coordinator.GetCompoenent<TransformComponent>(e);
			glm::vec3 _position = component.Position;
			glm::vec3 _size = component.Scale;

			if (this->bounds.Contains(_position, _size))
				return this->mEntities;

		}

		
	}

}