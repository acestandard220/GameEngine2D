#include "CollisionSystem.h"
#include <iostream>
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
	if (object.position.x <= LEFT_BOUND)
	{
		object.velocity.x *= -1;
		std::cout << "Left bounds collision\n";
		return true;
	}
	if (object.position.x + object.size.x >= RIGHT_BOUND)
	{
		object.velocity.x *= -1;
		std::cout << "Right bounds collision\n";
		return true;
	}

	if (object.position.y <= BOTTOM_BOUND)
	{
		object.velocity.y *= -1;
		std::cout << "Bottom bounds collision\n";
		return true;
	}
	if (object.position.y + object.size.y  >= TOP_BOUND)
	{
		object.velocity.y *= -1;
		std::cout << "Top bounds collision\n";
		return true;
	}
	return false;
}

bool CollisionSystem::OnOtherCollided(GameObject& object)
{
	for (auto& obj : mObjects)
	{
		if ( (object.GetMax().x >= obj->GetMin().x && object.GetMin().x <= obj->GetMax().x) &&
			 (object.GetMax().y >= obj->GetMin().y && object.GetMin().y <= obj->GetMax().y) )
		{
			std::cout << "Collision has happened with "<< obj->name << "\n";
		}
	}
	return true;
}



void QuadTree::Initialize()
{
	debug_renderer_data = new SubDebugRendererData;
	{
		glGenVertexArrays(1, &debug_renderer_data->vao);
		glBindVertexArray(debug_renderer_data->vao);

		glGenBuffers(1, &debug_renderer_data->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, debug_renderer_data->vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
	{
		const char* vertex_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            
            void main()
            {
                gl_Position = vec4(aPos,1.0f);
            }

		)";

		const char* fragment_source = R"(
            #version 330 core
            out vec4 FragColor;
            
            void main()
            {
                FragColor = vec4(0.3f,1.0f,0.3f,1.0f);
            }
		)";

		uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
		glShaderSource(fragment_shader, 1, &fragment_source, nullptr);

		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);

		debug_renderer_data->program = glCreateProgram();
		glAttachShader(debug_renderer_data->program, vertex_shader);
		glAttachShader(debug_renderer_data->program, fragment_shader);

		glLinkProgram(debug_renderer_data->program);

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

		glGetShaderiv(debug_renderer_data->program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(debug_renderer_data->program, 512, NULL, infoLog);
			std::cout << infoLog;
		}
	}
	glLineWidth(2.0f);
}

QuadTree::QuadTree(int lev, glm::vec3 pos, glm::vec2 size)
	:level(lev),position(pos),size(size)
{
	Initialize();
}

void QuadTree::Render(glm::vec3 pos, glm::vec2 size, uint32_t offset)
{
	glm::vec3 points[8] = {
		{ pos },
		{ pos.x ,pos.y + size.y,pos.z },

		{ pos.x ,pos.y + size.y,pos.z },
		{ pos.x + size.x ,pos.y + size.y,pos.z },

		{ pos.x + size.x ,pos.y + size.y,pos.z },
		{ pos.x + size.x,pos.y,pos.z },

		{ pos.x + size.x,pos.y,pos.z },
		{ pos },
	};

	glBindVertexArray(debug_renderer_data->vao);
	glBindBuffer(GL_ARRAY_BUFFER, debug_renderer_data->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(points), points);

	glDrawArrays(GL_LINE, 0, 8);
}

void QuadTree::Insert(GameObject& object)
{
	//Check if there has been a split
	if (northWest)
	{

	}

	mObjects.push_back(&object);


	if (level != MAX_LEVELS && mObjects.size() >= MAX_PER_QUAD)
	{
		Split();

		std::vector<GameObject*> new_objects = std::move(mObjects);

		for (auto x : new_objects)
		{
			Insert(*x);
		}
	}

	
}

void QuadTree::Split()
{
	glm::vec3 new_position = position;
	glm::vec2 new_size = { size.x / 2,size.y / 2 };

	southWest = std::make_shared<QuadTree>(level + 1, new_position, new_size);
	southEast = std::make_shared<QuadTree>(level + 1, glm::vec3(new_position.x + new_size.x,new_position.y,0.0f), new_size);
	
	northWest = std::make_shared<QuadTree>(level + 1, glm::vec3(new_position.x,new_position.y+size.y,0.0f), new_size);
	northEast = std::make_shared<QuadTree>(level + 1, glm::vec3(new_position.x + size.x, new_position.y + size.y,0.0f), new_size);
}
