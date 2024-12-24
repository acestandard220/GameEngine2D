#pragma once
#include <iostream>
#include <cstdint>

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Texture2D.h"
#include "Sprite.h"
#include "../AssetManager/AssetManager.h"

class GameObject;

static const char* vertex_source = R"(
		#version 330 core
		layout (location =0) in vec3 aPos;
		layout (location =1) in vec2 aTex;

        uniform mat4 vp;
        uniform mat4 model;
		
		out vec2 Tex;
		void main()
		{
			gl_Position = vp * vec4(aPos,1.0f);
			Tex = aTex;
		}		
	)";

static const char* fragment_source = R"(
		#version 330 core
		out vec4 FragColor;
		
		uniform sampler2D text;
		uniform vec3 color;

		in vec2 Tex;
		void main()
		{
			vec4 texture_color = texture(text,Tex);
			if(texture_color.a < 0.1f)
			{
				discard;
			}

			FragColor = vec4(color,1.0f) * texture_color;
		}		
	)";

class Renderer
{
	struct VertexType
	{
		glm::vec3 position;
		glm::vec2 texture_coord;
	};

	static int shared_offset;
	static int shared_draw_count;
	public:
		static bool Initialize();
		static void DrawQuad(GameObject& object);
		static void EndScene();


	
	private:

		static std::shared_ptr<Texture2D> white_texture;
		static glm::mat4 view;
		static glm::mat4 proj;

		static glm::mat4 model;

		static uint32_t vao;
		static uint32_t vbo;
		static uint32_t program;
};