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
			//std::cout << "Tag System OnUpdate\n";
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
	}
}
