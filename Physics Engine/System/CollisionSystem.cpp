#include "CollisionSystem.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

#define TIMER_TRACK(name) auto name## = glfwGetTime(); 
#define TIMER_STAMP(name) std::cout<<"[TIME_STAMP:["<<#name<<"]]: "<<(glfwGetTime()-name##) <<std::endl;

std::vector<GameObject*> CollisionSystem::mObjects;

bool CollisionSystem::Initialize()
{

	return false;
}

bool CollisionSystem::OnUpdate()
{
	return false;
}

bool CollisionSystem::OnBoundsCollided(GameObject& object)
{
	if (object.bounds.position.x <= LEFT_BOUND)
	{
		object.velocity.x *= -1;
		//std::cout << "Left bounds collision\n";
		return true;
	}
	if (object.bounds.position.x + object.bounds.size.x >= RIGHT_BOUND)
	{
		object.velocity.x *= -1;
		//std::cout << "Right bounds collision\n";
		return true;
	}

	if (object.bounds.position.y <= BOTTOM_BOUND)
	{
		object.velocity.y *= -1;
		//std::cout << "Bottom bounds collision\n";
		return true;
	}
	if (object.bounds.position.y + object.bounds.size.y  >= TOP_BOUND)
	{
		object.velocity.y *= -1;
		//std::cout << "Top bounds collision\n";
		return true;
	}
	return false;
}

bool CollisionSystem::OnOtherCollided(GameObject& object)
{
	//Bad Collision Check
	for (auto& obj : mObjects)
	{
		if ( (object.bounds.GetMax().x >= obj->bounds.GetMin().x && object.bounds.GetMin().x <= obj->bounds.GetMax().x) &&
			 (object.bounds.GetMax().y >= obj->bounds.GetMin().y && object.bounds.GetMin().y <= obj->bounds.GetMax().y) )
		{
			// Adjust positions to centers
			float objCenterX = obj->bounds.position.x - obj->bounds.size.x/2;
			float objCenterY = obj->bounds.position.y - obj->bounds.size.x/2;

			float objectCenterX = object.bounds.position.x - object.bounds.size.x / 2;
			float objectCenterY = object.bounds.position.y - object.bounds.size.x / 2;

			// Calculate the normal vector
			float dx = objCenterX - objectCenterX;
			float dy = objCenterY - objectCenterY;
			float distance = std::sqrt(dx * dx + dy * dy);

			// Check for zero distance (to avoid NaN)
			if (distance == 0) {
				return false;  // No collision resolution, as objects overlap
			}

			// Normalize the normal vector
			float nx = dx / distance;
			float ny = dy / distance;

			// Calculate the relative velocity
			float rvx = obj->velocity.x - object.velocity.x;
			float rvy = obj->velocity.y - object.velocity.y;

			// Calculate the relative velocity in the normal direction
			float vn = rvx * nx + rvy * ny;

			// If balls are moving apart, no need to resolve
			if (vn > 0) return false;

			// Calculate the impulse scalar (assuming equal mass)
			float impulse = -2 * vn / 2;

			// Apply impulse to each ball
			object.velocity.x -= impulse * nx;
			object.velocity.y -= impulse * ny;
			obj->velocity.x += impulse * nx;
			obj->velocity.y += impulse * ny;

		}
	}
	return true;
}


bool CollisionSystem::OnOtherCollided(GameObject& object, std::vector<GameObject*> possible_object)
{
	//Bad Collision Check
	for (auto& obj : possible_object)
	{
		if (obj == &object)
			continue;
		if ((object.bounds.GetMax().x >= obj->bounds.GetMin().x && object.bounds.GetMin().x <= obj->bounds.GetMax().x) &&
			(object.bounds.GetMax().y >= obj->bounds.GetMin().y && object.bounds.GetMin().y <= obj->bounds.GetMax().y))
		{
			// Adjust positions to centers
			float objCenterX = obj->bounds.position.x - obj->bounds.size.x / 2;
			float objCenterY = obj->bounds.position.y - obj->bounds.size.x / 2;

			float objectCenterX = object.bounds.position.x - object.bounds.size.x / 2;
			float objectCenterY = object.bounds.position.y - object.bounds.size.x / 2;

			// Calculate the normal vector
			float dx = objectCenterX - objCenterX;
			float dy = objectCenterY - objCenterY;
			float distance = std::sqrt(dx * dx + dy * dy);

			// Check for zero distance (to avoid NaN)
			if (distance == 0) {
				return false;  // No collision resolution, as objects overlap
			}

			// Normalize the normal vector
			float nx = dx / distance;
			float ny = dy / distance;

			// Calculate the relative velocity
			float rvx = object.velocity.x - obj->velocity.x;
			float rvy = object.velocity.y - obj->velocity.y;

			// Calculate the relative velocity in the normal direction
			float vn = rvx * nx + rvy * ny;

			// If balls are moving apart, no need to resolve
			if (vn > 0) return false;

			// Calculate the impulse scalar (assuming equal mass)
			float impulse = -2 * vn / 2;

			// Apply impulse to each ball
			object.velocity.x += impulse * nx;
			object.velocity.y += impulse * ny;
			obj->velocity.x -= impulse * nx;
			obj->velocity.y -= impulse * ny;
		}
	}
	return true;
}



void QuadTree::Initialize()
{
	
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
	{
		const char* vertex_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

			uniform mat4 vp;
            
            void main()
            {
                gl_Position = vp * vec4(aPos,1.0f);
            }

		)";

		const char* fragment_source = R"(
            #version 330 core
            out vec4 FragColor;
            
            void main()
            {
                FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
            }
		)";

		uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
		glShaderSource(fragment_shader, 1, &fragment_source, nullptr);

		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);

		int success;
		char infoLog[512];
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
			std::cout << infoLog;
		}

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
			std::cout << infoLog;
		}

		glGetShaderiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(program, 512, NULL, infoLog);
			std::cout << infoLog;
		}
	}
	glLineWidth(2.0f);
}


QuadTree::QuadTree(int lev, glm::vec3 pos, glm::vec2 size)
	:level(lev), Bounds(pos, size)
{
	//Initialize();
	
	//Render();//0.0001
	
}

QuadTree::~QuadTree()
{
	//glDeleteBuffers(1, &vbo);
	//glDeleteVertexArrays(1, &vao);
	//glDeleteProgram(program);
}


void QuadTree::GetTreeStats()
{
	
}

void QuadTree::Render()
{
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f);

	glm::mat4 vp = proj * view;

	glm::vec3 vertices[8] =
	{
		{ Bounds.position },
		{ Bounds.position.x,Bounds.position.y + Bounds.size.y ,0.0f},

		{ Bounds.position.x, Bounds.position.y + Bounds.size.y, 0.0f},
		{ Bounds.position.x + Bounds.size.x , Bounds.position.y + Bounds.size.y, 0.0f},

		{ Bounds.position.x + Bounds.size.x , Bounds.position.y + Bounds.size.y, 0.0f},
		{ Bounds.position.x + Bounds.size.x , Bounds.position.y, 0.0f},
		
		{ Bounds.position.x + Bounds.size.x , Bounds.position.y, 0.0f},
		{ Bounds.position }
	};

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "vp"), 1, GL_FALSE, &vp[0][0]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glDrawArrays(GL_LINES, 0, 8);
}

void QuadTree::Insert(GameObject& object)
{
	if (northWest)
	{
		auto quads = GetQuads(&object);

		for (auto x : quads)
		{
			x->Insert(object);
		}
		return;
	}

	mObjects.push_back(&object);

	if (level >= MAX_LEVELS)
	{
		//std::cout << "The Limit has been hit\n";
		return;
	}

	if (this->level < MAX_LEVELS && mObjects.size() > MAX_PER_QUAD)
	{
		Split();
		for (auto x : mObjects)
		{
			Insert(*x);
		}
		mObjects.clear();
	}


}

bool QuadTree::Remove(GameObject& object)
{
	if (northEast)
	{
		if (northEast->Remove(object))
			return true;
		if (northWest->Remove(object))
			return true;
		if (southEast->Remove(object))
			return true;
		if (southWest->Remove(object))
			return true;
	}

	if (this->Bounds.Contains(object.bounds))
	{
		auto it = std::find(mObjects.begin(), mObjects.end(), &object);
		if(it != mObjects.end())
		{
			mObjects.erase(it);
			return true;
		}
	
	}
	return false;
}

std::vector<QuadTree*> QuadTree::GetQuads(GameObject* object)
{
	std::vector<QuadTree*> quads;
	if (northWest->Bounds.Contains(object->bounds))
	{
		quads.push_back(northWest.get());
	}
	if (northEast->Bounds.Contains(object->bounds))
	{
		quads.push_back(northEast.get());
	}
	if (southEast->Bounds.Contains(object->bounds))
	{
		quads.push_back(southEast.get());
	}
	if (southWest->Bounds.Contains(object->bounds))
	{
		quads.push_back(southWest.get());
	}
	return quads;
}

void QuadTree::Split()
{
	glm::vec3 new_position = Bounds.position;
	glm::vec2 new_size = { Bounds.size.x / 2,Bounds.size.y / 2 };

	southWest = std::make_shared<QuadTree>(level + 1, new_position, new_size);
	southEast = std::make_shared<QuadTree>(level + 1, glm::vec3(new_position.x + new_size.x,new_position.y,0.0f), new_size);
	
	northWest = std::make_shared<QuadTree>(level + 1, glm::vec3(new_position.x,new_position.y+ new_size.y,0.0f), new_size);
	northEast = std::make_shared<QuadTree>(level + 1, glm::vec3(new_position.x + new_size.x, new_position.y + new_size.y,0.0f), new_size);	
}

void QuadTree::Clear()
{
	northEast.reset();
	northWest.reset();
	southEast.reset();
	southWest.reset();
	mObjects.clear();
}

std::vector<GameObject*> QuadTree::GetFriendObjects(GameObject& object)
{
	std::vector<GameObject*> temp_objects;
	if (northEast)
	{
		std::vector<GameObject*> NE = northEast->GetFriendObjects(object);
		if (NE.size() != 0)
		{
			return NE;
		}
		std::vector<GameObject*> NW = northWest->GetFriendObjects(object);
		if (NW.size() != 0)
		{
			return NW;
		}
		std::vector<GameObject*> SE = southEast->GetFriendObjects(object);
		if (SE.size() != 0)
		{
			return SE;
		}
		std::vector<GameObject*> SW = southWest->GetFriendObjects(object);
		if (SW.size() != 0)
		{
			return SW;
		}

	}

	if (this->Bounds.Contains(object.bounds))
	{
		std::vector<GameObject*> temp = mObjects;
		return temp;
	}
}

void QuadTree::Traverse()
{
	if (northEast)
	{
		northEast->Traverse();
		northWest->Traverse();
		southEast->Traverse();
		southWest->Traverse();
	}
	Render();
}
