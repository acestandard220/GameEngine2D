#include "Systems.h"
#include "renderer2d.h"
namespace GE2D {
	namespace ECS
	{
		inline const std::string& TagSystem::GetEntityTag(TagComponent tagcomponent) const
		{
			return tagcomponent.Tag;
		}

		void TagSystem::SetTag(TagComponent& tagcomponent, std::string& tag)
		{
			tagcomponent.Tag = tag;
		}
		
		void TagSystem::OnUpdate(void* co)
		{
			Coordinator* coordinator = (Coordinator*)co;
			for (auto entity : enitites)
			{
				auto& x = coordinator->GetCompoenent<TagComponent>(entity);
			}
		}
		
		void SpriteMeshRenderer::OnUpdate(void* co)
		{
			Coordinator* coordinator = (Coordinator*)co;
			 
			for (auto entity : enitites)
			{
				auto& SpriteMesh = coordinator->GetCompoenent<SpriteMeshComponent>(entity);
				TransformComponent* Transform = &coordinator->GetCompoenent<TransformComponent>(entity);

				Renderer2D::DrawQuad(Transform->Position,Transform->Scale,Transform->Rotation,SpriteMesh.Color);
		 	}
		}


		void CollisionSystem::OnUpdate(void* co)
		{
			Coordinator* coordinator = (Coordinator*)co;
			coordinator->spatial_partition->Clear();
			for (auto entity : enitites)
				coordinator->spatial_partition->Insert(entity);
			
			for (auto entity : enitites)
			{

			}
			coordinator->spatial_partition->Clear();
		}


		void PlayerControllSystem::OnUpdate(void* co)
		{
			Coordinator* coordinator = (Coordinator*)co;
			for (auto entity : enitites)
			{
				auto component = coordinator->GetCompoenent<PlayerControllerComponent>(entity);
				component.ControlCallback(coordinator);
			}
		}
	}
}
