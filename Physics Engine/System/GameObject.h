 #pragma once
#include "../Renderer/Sprite.h"
#include <string>
#include <iostream>

struct AABB
{
	glm::vec3 position;
	glm::vec2 size;

	AABB(glm::vec3 pos, glm::vec2 sz) :position(pos), size(sz) {}
	AABB(const AABB& other) = default;

	glm::vec2 GetMin()const;
	glm::vec2 GetMax()const;

	bool Contains(AABB& object)
	{
		if (object.GetMax().x <= this->GetMax().x && object.GetMin().x >= this->GetMin().x)
		{
			if (object.GetMax().y <= this->GetMax().y && object.GetMin().y >= this->GetMin().y)
			{
				return true;
			}
		}
		return false;
	}
};


class GameObject
{
public:
	GameObject(glm::vec3 pos, glm::vec2 size, glm::vec3 vel,Sprite& sprite);
	virtual ~GameObject() {
		std::cout << "A GameObject has been destroyed.\n";
	}

	virtual void OnUpdate(float) = 0;
	virtual void Kill() = 0;

	glm::vec3 velocity;

	AABB bounds;  

	Sprite* sprite;

	std::string name;
	static int count;

	inline bool operator== (const GameObject& other)const
	{
		return this == &other;
	}
};


class Ball :public GameObject
{
public:
	Ball(glm::vec3 pos, glm::vec2 size, glm::vec3 vel, Sprite& sp);
	virtual ~Ball() {
		std::cout << "A Ball has been destroyed.\n";
	}

	virtual void OnUpdate(float dt)override;
	virtual void Kill()override;
private:
	glm::vec2 center;
	float diameter;
};
