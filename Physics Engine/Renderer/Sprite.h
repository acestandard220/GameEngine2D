#pragma once
#include <glm/glm.hpp>
#include <glm/vector_relational.hpp>

#include "Texture2D.h"
#include <memory>

struct Sprite
{
	Sprite();
	Sprite(glm::vec3 col);
	~Sprite();

	const uint32_t GetTexture()const { return texture->GetID(); }
	const glm::vec3& GetColor()const { return color; }

	void LoadTexture(const char* name);
	void SetColor(glm::vec3 color);

	inline const bool IsTextured()const { return textured; }

private:
	bool textured = false;
	std::shared_ptr<Texture2D> texture;
	glm::vec3 color;
};
