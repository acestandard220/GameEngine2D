#include "Renderer2D.h"
#include "../System/GameObject.h"

std::shared_ptr<Texture2D> Renderer::white_texture = nullptr;
glm::mat4 Renderer::view = glm::mat4(1.0f);
glm::mat4 Renderer::proj = glm::mat4(1.0f);
glm::mat4 Renderer::model = glm::mat4(1.0f);

uint32_t Renderer::vao = 0;
uint32_t Renderer::vbo = 0;
uint32_t Renderer::program = 0;

bool Renderer::Initialize()
{
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	{
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

	{
		AssetManager::LoadTexture("White Texture", "white.png");
		white_texture = AssetManager::GetTexture("White Texture");
	}

	{
		view = glm::lookAt(glm::vec3( 0.0f,0.0f,3.0f ), glm::vec3( 0.0f,0.0f,0.0f ), glm::vec3( 0.0f,1.0f,0.0f ));
		proj = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)800.0f, 0.1f, 100.0f);
	}

	return true;
}

void Renderer::DrawQuad(Sprite& sprite, glm::vec3 position, glm::vec2 size)
{
	VertexType *vertex_data = new VertexType[6];
	vertex_data[0].position = { position };
	vertex_data[0].texture_coord = { 0.0f, 0.0f };

	vertex_data[1].position = { position.x, position.y + size.y, 0.0f };
	vertex_data[1].texture_coord = { 0.0f, 1.0f };

	vertex_data[2].position = { position.x + size.x, position.y + size.y, 0.0f };
	vertex_data[2].texture_coord = { 1.0f, 1.0f };

	vertex_data[3].position = { position.x,position.y,0.0f };
	vertex_data[3].texture_coord = { 0.0f, 0.0f };

	vertex_data[4].position = { position.x + size.x,position.y,0.0f };
	vertex_data[4].texture_coord = { 1.0f, 0.0f };

	vertex_data[5].position = { position.x + size.x, position.y + size.y, 0.0f };
	vertex_data[5].texture_coord = { 1.0f, 1.0f };

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*30, vertex_data, GL_DYNAMIC_DRAW);

	glUseProgram(program);

	glUniform1i(glGetUniformLocation(program, "text"), 0);
	glActiveTexture(GL_TEXTURE0);
	if (sprite.IsTextured())
	{
		glBindTexture(GL_TEXTURE_2D, sprite.GetTexture());
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, white_texture->GetID());
	}
	
	glUniform3f(glGetUniformLocation(program, "color"), sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z);

	glm::mat4 vp = proj * view;
	glUniformMatrix4fv(glGetUniformLocation(program, "vp"), 1, GL_FALSE, &vp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}



void Renderer::DrawQuad(GameObject& object)
{
	VertexType* vertex_data = new VertexType[6];
	vertex_data[0].position = { object.position };
	vertex_data[0].texture_coord = { 0.0f, 0.0f };

	vertex_data[1].position = { object.position.x, object.position.y + object.size.y, 0.0f };
	vertex_data[1].texture_coord = { 0.0f, 1.0f };

	vertex_data[2].position = { object.position.x + object.size.x,object.position.y + object.size.y, 0.0f };
	vertex_data[2].texture_coord = { 1.0f, 1.0f };

	vertex_data[3].position = { object.position.x,object.position.y,0.0f };
	vertex_data[3].texture_coord = { 0.0f, 0.0f };

	vertex_data[4].position = { object.position.x + object.size.x,object.position.y,0.0f };
	vertex_data[4].texture_coord = { 1.0f, 0.0f };

	vertex_data[5].position = { object.position.x + object.size.x, object.position.y + object.size.y, 0.0f };
	vertex_data[5].texture_coord = { 1.0f, 1.0f };

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, vertex_data, GL_DYNAMIC_DRAW);

	glUseProgram(program);

	glUniform1i(glGetUniformLocation(program, "text"), 0);
	glActiveTexture(GL_TEXTURE0);
	if (object.sprite->IsTextured())
	{
		glBindTexture(GL_TEXTURE_2D, object.sprite->GetTexture());
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, white_texture->GetID());
	}

	glUniform3f(glGetUniformLocation(program, "color"), object.sprite->GetColor().x, object.sprite->GetColor().y, object.sprite->GetColor().z);

	glm::mat4 vp = proj * view;
	glUniformMatrix4fv(glGetUniformLocation(program, "vp"), 1, GL_FALSE, &vp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}
