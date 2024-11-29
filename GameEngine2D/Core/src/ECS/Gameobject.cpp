#include "Gameobject.h"

//namespace GE2D {
//    namespace ECS {
//
//        GameObject::GameObject(std::shared_ptr<Scene> scene)
//        {
//            mAssociartedScene = scene;
//            ID = mAssociartedScene->coordinator.CreateEntity();
//            mAssociartedScene->AddEntity(ID);
//        }
//        void GameObject::DeleteGameObject()
//        {
//            mAssociartedScene->coordinator.DestroyEntity(ID);
//            mAssociartedScene->RemoveEntity(ID);
//        }
//
//        Entity GameObject::GetGameObjectID()const
//        {
//            return ID;
//        }
//
//        template <typename T>
//        void GameObject::AddComponent(T component)
//        { 
//            mAssociartedScene->coordinator.AddComponent<T>(ID, component);
//        }
//
//        template<typename T>
//        void GameObject::RemoveComponent()
//        {
//            mAssociartedScene->coordinator.RemoveComponent<T>(ID);
//        }
//
//        template<typename T>
//        T& GameObject::GetComponent()
//        {
//            mAssociartedScene->coordinator.GetCompoenent<T>(ID);
//        }
//
//    }
//}
