#pragma once
#include "Scene.h"
#include "pch.h"

namespace GE2D
{
    namespace ECS
    {

        class GameObject
        {
        public:
            GameObject() = default;
            GameObject(std::shared_ptr<Scene> scene)
            {
                mAssociartedScene = scene;
                ID = mAssociartedScene->coordinator.CreateEntity();
                name = "GameOBject" + std::to_string(mAssociartedScene->GetRegisteredEntities());
                mAssociartedScene->AddEntity(*this,ID);
            }
            ~GameObject()
            {
                DeleteGameObject();
            }
           
            inline void DeleteGameObject()
            {
                mAssociartedScene->coordinator.DestroyEntity(ID);
                mAssociartedScene->RemoveEntity(*this,ID);
            }

            
            inline Entity GetGameObjectID()const
            {
                return ID;
            }

            template <typename T>
            inline void AddComponent(T& component)
            {
                mAssociartedScene->coordinator.AddComponent<T>(ID, component);
            }

            template <typename T> 
            inline void RemoveComponent()
            {
                mAssociartedScene->coordinator.RemoveComponent<T>(ID);
            }

            template <typename T>
            inline T& GetComponent()
            {
                return mAssociartedScene->coordinator.GetCompoenent<T>(ID);
            }

            std::string& GetGameObjectName() { return name; }
        
        private:
            Entity ID;
            std::string name;
            std::shared_ptr<Scene> mAssociartedScene = nullptr;
        };

        using GameObjectRef = std::shared_ptr<GameObject>;

    }
}