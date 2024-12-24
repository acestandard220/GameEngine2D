#pragma once

constexpr float LEFT_BOUND = -10.0f;
constexpr float RIGHT_BOUND = 10.0f;

constexpr float TOP_BOUND = 10.0f;
constexpr float BOTTOM_BOUND = -10.0f;

constexpr size_t VECTOR2_SIZE = sizeof(float) * 2;
constexpr size_t VECTOR3_SIZE = sizeof(float) * 3;
constexpr size_t VECTOR4_SIZE = sizeof(float) * 4;

#include "GameObject.h"
#include <vector>

class CollisionSystem
{
public:
	static bool Initialize();
	static bool OnUpdate();

	static bool OnBoundsCollided(GameObject& object);
	static bool OnOtherCollided(GameObject& object);

	static bool OnOtherCollided(GameObject& object, std::vector<GameObject*> possible_object);

	static std::vector<GameObject*> mObjects;
};

class QuadTree
{
	uint32_t vao;
	uint32_t vbo;

	uint32_t program;
public:
	const int MAX_LEVELS = 2000;
	const int MAX_PER_QUAD = 500;


	QuadTree(int lev, glm::vec3 position, glm::vec2 size);
	~QuadTree();
	void Insert(GameObject& object);
	bool Remove(GameObject& object);
	void Clear();

	std::vector<GameObject*> GetFriendObjects(GameObject& object);

	void Traverse();

	void GetTreeStats();
	void Render();

private:
	void Split();
	std::vector<QuadTree*> GetQuads(GameObject* object);

	void Initialize();
private:
	AABB Bounds;

	int level;

	std::vector<GameObject*>mObjects;

	std::shared_ptr<QuadTree> northWest;
	std::shared_ptr<QuadTree> northEast;
	std::shared_ptr<QuadTree> southWest;
	std::shared_ptr<QuadTree> southEast;
};


