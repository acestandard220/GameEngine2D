#include "GameObject.h"

int GameObject::count = 0;

GameObject::GameObject(glm::vec3 pos, glm::vec2 size, glm::vec3 vel,Sprite& sprite)
	:position(pos), size(size),velocity(vel),sprite(&sprite),name("GameObject"+ std::to_string(count))
{
	count++;
}


Ball::Ball(glm::vec3 pos, glm::vec2 size, glm::vec3 vel,Sprite& sp)
	:GameObject(pos, size, vel,sp)
{
	diameter = size.x / 2;
	center = { position.x + diameter / 2,position.y + diameter / 2 };
}

void Ball::OnUpdate()
{
	position += velocity * 0.005f;
	center = { position.x + diameter / 2,position.y + diameter / 2 };
}

glm::vec2 GameObject::GetMin() const
{
	return glm::vec2(position.x, position.y);
}

glm::vec2 GameObject::GetMax() const
{
	return glm::vec2(position.x + size.x, position.y +size.y);
}
