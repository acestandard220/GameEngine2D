#pragma once
#include "rendercommand.h"
#include "Shader.h"
#include "Camera.h"

class Renderer2D
{
public:
	static void Init();
	static void BeginScene(OrthographicCamera& camera);

	static void EndScene();

	static void Flush();

	static void DrawQuad(glm::vec3& position, float size, glm::vec3 color);

	static void DrawQuad(glm::vec3& position, glm::vec3& scale, glm::vec3& rotation, glm::vec3 color);
	static void DrawQuad(glm::vec3& position, glm::vec3& scale, glm::vec3& rotation);


};