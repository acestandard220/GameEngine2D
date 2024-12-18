#pragma once

constexpr float LEFT_BOUND = -1.256f;
constexpr float RIGHT_BOUND = 1.26f;

constexpr float TOP_BOUND = 1.26f;
constexpr float BOTTOM_BOUND =-1.26f;

#include "GameObject.h"
#include <vector>

class CollisionSystem
{
public:
	static bool Initialize();
	static bool OnUpdate();

	static bool OnBoundsCollided(GameObject& object);
	static bool OnOtherCollided(GameObject& object);

	static std::vector<GameObject*> mObjects;
};

class QuadTree
{
	struct SubDebugRendererData
	{
		uint32_t vao;
		uint32_t vbo;
		uint32_t program;
	};
	SubDebugRendererData* debug_renderer_data;
	void Initialize();
public:
	const int MAX_LEVELS = 10;
	const int MAX_PER_QUAD = 2;

	QuadTree(int lev, glm::vec3 position, glm::vec2 size);

	void Render(glm::vec3 pos, glm::vec2 size, uint32_t offset);

	void Insert(GameObject& object);

	void Split();
private:
	glm::vec3 position;
	glm::vec2 size;

	int level;

	std::vector<GameObject*>mObjects;

	std::shared_ptr<QuadTree> northWest;
	std::shared_ptr<QuadTree> northEast;
	std::shared_ptr<QuadTree> southWest;
	std::shared_ptr<QuadTree> southEast;

};