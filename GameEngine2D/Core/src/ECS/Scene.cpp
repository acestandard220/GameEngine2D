#include "Scene.h"
#include "Gameobject.h"
#include "Components.h"
#include "Systems.h"

namespace GE2D
{
	namespace ECS
	{

		Scene::Scene(const char* name) :mSceneName(name)
		{
			coordinator.Init();
			RegisterComponents();
			RegisterSystems();
		}

		Scene::~Scene()
		{
			DestroyScene();
		}

		void Scene::DestroyScene()
		{
			//TODO: Destroy scene
		}

		void Scene::OnUpdate()
		{
			//Main shit...
			coordinator.OnUpdate();
		}

		std::shared_ptr<GameObject> Scene::AddGameObject()
		{		
			return std::make_shared<GameObject>(shared_from_this());
		}

		void Scene::DestroyGameObject(GameObject& g)
		{
			g.DeleteGameObject();
		}


		void Scene::AddEntity(GameObject& g,Entity e)
		{
			mAssociatedEntities.insert({g.GetGameObjectName(),e});
		}

		void Scene::RemoveEntity(GameObject& g,Entity e)
		{
			mAssociatedEntities.erase(g.GetGameObjectName());
		}

		const std::string& Scene::GetSceneName() const
		{
			return mSceneName;
		}

		void Scene::SetSceneName(std::string& name)
		{
			mSceneName = name;
		}

		void Scene::RegisterComponents()
		{
			auto TagCompSignMap = coordinator.RegisterComponent<TagComponent>();
			auto TranformCompSignMap = coordinator.RegisterComponent<TransformComponent>();
			auto SpriteMeshComSignMap = coordinator.RegisterComponent<SpriteMeshComponent>();
		}

		void Scene::RegisterSystems()
		{
			coordinator.RegisterSystem<TagSystem>();
			Signature tagSysSignature;
			tagSysSignature.set(coordinator.GetCompoenentType<TagComponent>(), true);
			coordinator.SetSystemSignature<TagSystem>(tagSysSignature);

			coordinator.RegisterSystem<SpriteMeshRenderer>();
			Signature spriteMeshRenSignature;
			spriteMeshRenSignature.set(coordinator.GetCompoenentType<TransformComponent>(), true);
			spriteMeshRenSignature.set(coordinator.GetCompoenentType<SpriteMeshComponent>(), true);
			coordinator.SetSystemSignature<SpriteMeshRenderer>(spriteMeshRenSignature);
		}

		void Scene::SetSystemSignatures()
		{
		}


	}
}
