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

			    void OnUpdate(void*) override;

		};

		//NOT COMPLETE CANNOT be used
		class CollisionSystem : public ISystem
		{
			public:
				CollisionSystem() = default;

				void OnUpdate(void*) override;
		};

		class PlayerControllSystem : public ISystem
		{
		public:
			PlayerControllSystem() = default;

			void OnUpdate(void*) override;

		};

	}
}