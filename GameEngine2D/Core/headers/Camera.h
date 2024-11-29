#pragma once
#include "pch.h"

class OrthographicCamera
{
	public:
		OrthographicCamera(float, float, float, float);

		void SetPosition(glm::vec3& pos);
		const glm::vec3& GetPosition() const;

		void SetRotation(float rot);
		const float& GetRotation()const;

		void SetProjection(float, float, float, float);
		glm::mat4 GetProjection()const;
		glm::mat4 GetView()const;
		glm::mat4 GetViewProjection()const;


    private:
		void Recalculate();
    private:

		glm::mat4 m_viewmatrix;
		glm::mat4 m_projectionmatrix;
		glm::mat4 m_viewprojection;

		glm::vec3 m_position = {0.0f,0.0f,0.0f};
		float m_rotation = 0.0f;

};