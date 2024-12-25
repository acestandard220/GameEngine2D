#include "GameObject.h"

int GameObject::count = 0;


glm::vec2 AABB::GetMin() const
{
	return glm::vec2(position.x, position.y);
}

glm::vec2 AABB::GetMax() const
{
	return glm::vec2(position.x + size.x, position.y + size.y);
}

GameObject::GameObject(glm::vec3 pos, glm::vec2 size, glm::vec3 vel,Sprite& sprite)
	:bounds(pos, size), velocity(vel), sprite(&sprite), name("GameObject"+ std::to_string(count))
{
	count++;
}


Ball::Ball(glm::vec3 pos, glm::vec2 size, glm::vec3 vel,Sprite& sp)
	:GameObject(pos, size, vel,sp)
{
	diameter = size.x / 2;
	center = { bounds.position.x + diameter / 2,bounds.position.y + diameter / 2 };
}

void Ball::OnUpdate(float dt)
{
	bounds.position += velocity * dt;
	center = { bounds.position.x + diameter / 2, bounds.position.y + diameter / 2 };
}

void Ball::Kill()
{
	delete this;
}

