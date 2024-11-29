#pragma once
#include "Coordinator.h"
#include "Texture.h"


namespace GE2D
{
	namespace ECS
	{
		struct TagComponent
		{
			std::string Tag;
			TagComponent(const char* tag):Tag(tag)
			{ }
			TagComponent() = default;

			operator const std::string& const() { return Tag; }
		};

		struct TransformComponent
		{
			glm::vec3 Position {0.0f, 0.0f, 0.0f};
			glm::vec3 Scale    {0.0f, 0.0f, 0.0f};
			glm::vec3 Rotation {0.0f, 0.0f, 0.0f};
		};

		struct SpriteMeshComponent
		{
			glm::vec4 Color{ 1.0f,1.0f,1.0f,1.0f };
			//Texture* Sprite;

			SpriteMeshComponent() = default;
			SpriteMeshComponent(const SpriteMeshComponent& other) = default;
		};







	}
}