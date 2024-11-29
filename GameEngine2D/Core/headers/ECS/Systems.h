#pragma once
#include "Components.h"


namespace GE2D
{
	namespace ECS
	{
		class TagSystem : public ISystem
		{
		public:
			TagSystem() = default;
			const std::string& GetEntityTag(TagComponent tagcomponent)const;

			inline void SetTag(TagComponent& tagcomponent, std::string& tag);

			virtual void OnUpdate(void* co) override;

		};

		class SpriteMeshRenderer : public ISystem
		{
		    public:
			    SpriteMeshRenderer() = default;

			

			// Inherited via ISystem
			    void OnUpdate(void*) override;

		};

		

	}
}