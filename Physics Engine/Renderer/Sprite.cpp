#include "Sprite.h"
#include "../AssetManager/AssetManager.h"

Sprite::Sprite()
{
	texture = nullptr;
}

Sprite::Sprite( glm::vec3 col)
	:color(col)
{
	texture = nullptr;
}

Sprite::~Sprite()
{
}

void Sprite::LoadTexture(const char* name)
{
	texture = AssetManager::GetTexture(name);
	textured = true;
}

void Sprite::SetColor(glm::vec3 col)
{
	color = col;
}
