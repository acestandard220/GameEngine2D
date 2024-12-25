#include "ECS/Scene.h"
#include "ECS/Gameobject.h"
#include "ECS/Components.h"
#include "ECS/Systems.h"


namespace GE2D
{
	namespace ECS
	{

		Scene::Scene(const char* name) 
			:mSceneName(name)
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
			auto TagCompSignMap        = coordinator.RegisterComponent<TagComponent>();
			auto TranformCompSignMap   = coordinator.RegisterComponent<TransformComponent>();
			auto SpriteMeshComSignMap  = coordinator.RegisterComponent<SpriteMeshComponent>();
			auto BoxColliderComSignMap = coordinator.RegisterComponent<BoxCollider>();
			auto PlayerContCompSignMap = coordinator.RegisterComponent<PlayerControllerComponent>();
		}

		void Scene::RegisterSystems()
		{

			auto tagCompMap    = coordinator.GetCompoenentType<TagComponent>();
			auto transCompMap  = coordinator.GetCompoenentType<TransformComponent>();
			auto spriteCompMap = coordinator.GetCompoenentType<SpriteMeshComponent>();
			auto playerContrComMap = coordinator.GetCompoenentType<PlayerControllerComponent>();
				
			coordinator.RegisterSystem<TagSystem>();
			Signature tagSysSignature;
			tagSysSignature.set(tagCompMap, true);
			coordinator.SetSystemSignature<TagSystem>(tagSysSignature);

			coordinator.RegisterSystem<SpriteMeshRenderer>();
			Signature spriteMeshRenSignature;
			spriteMeshRenSignature.set(transCompMap, true);
			spriteMeshRenSignature.set(spriteCompMap, true);
			coordinator.SetSystemSignature<SpriteMeshRenderer>(spriteMeshRenSignature);


			coordinator.RegisterSystem<PlayerControllSystem>();
			Signature playerContrSysSignature;
			playerContrSysSignature.set(transCompMap, true);
			playerContrSysSignature.set(playerContrComMap, true);


		}

		void Scene::SetSystemSignatures()
		{
		}




		

	}
}
