#pragma once
#include "../Renderer/Sprite.h"
#include <string>

struct AABB
{
	glm::vec3 position;
	glm::vec2 size;

	bool Contains(AABB& object)
	{

	}
};


class GameObject
{
public:
	GameObject(glm::vec3 pos, glm::vec2 size, glm::vec3 vel,Sprite& sprite);

	virtual void OnUpdate() = 0;

	glm::vec2 GetMin()const;
	glm::vec2 GetMax()const;

	glm::vec3 position;
	glm::vec2 size;
	glm::vec3 velocity;

	AABB bounds;

	Sprite* sprite;


	std::string name;
	static int count;
};


class Ball :public GameObject
{
public:
	Ball(glm::vec3 pos, glm::vec2 size, glm::vec3 vel, Sprite& sp);

	virtual void OnUpdate()override;

	

private:
	glm::vec2 center;
	float diameter;
};
