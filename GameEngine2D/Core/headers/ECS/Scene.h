#pragma once
#include "Coordinator.h"
#include "pch.h"

namespace GE2D
{
	namespace ECS
	{
		class GameObject;

		class Scene : public std::enable_shared_from_this<Scene>
		{
		    public:
				Scene(const char* name);
			    Scene(const Scene& other) = default;
				~Scene();

				void DestroyScene();
			    
				void OnUpdate();

				std::shared_ptr<GameObject> AddGameObject();
				void DestroyGameObject(GameObject& g);

				/// @brief Returns the number of entities for a given scene
				uint32_t GetRegisteredEntities() const { return mAssociatedEntities.size(); }
				
				const std::string&  GetSceneName()const;
				void SetSceneName(std::string&);

				Coordinator& GetCoordinator() { return coordinator; }

			private:
				//Manual Registerations
				void RegisterComponents();
				void RegisterSystems();
				void SetSystemSignatures();

		    protected:
				friend class GameObject;
			    Coordinator coordinator;

				void AddEntity(GameObject&,Entity e);
				void RemoveEntity(GameObject& ,Entity e);
		    private:
				GE2D::ECS::uMapping<std::string, Entity> mAssociatedEntities;
				std::string mSceneName;
		};

		using SceneRef = std::shared_ptr<Scene>;
		using SceneScope = std::unique_ptr<Scene>;

	}
}