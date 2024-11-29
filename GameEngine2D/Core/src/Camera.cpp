#include "Camera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
    : m_projectionmatrix(glm::ortho(left,right, bottom, top,-1.0f,1000.0f)) ,
    m_viewmatrix(1.0f)
{
    m_viewprojection = m_projectionmatrix * m_viewmatrix;
}

void OrthographicCamera::SetPosition(glm::vec3& pos)
{
    m_position = pos;
    Recalculate();
}

const glm::vec3& OrthographicCamera::GetPosition() const
{
    return m_position;
}

void OrthographicCamera::SetRotation(float rot)
{
    m_rotation = rot;
    Recalculate();
}

const float& OrthographicCamera::GetRotation() const
{
    return m_rotation;
}

void OrthographicCamera::SetProjection(float left, float right, float top, float bottom)
{
    m_projectionmatrix = glm::ortho(left, right, bottom, top, -1.0f, 1000.0f);
    m_viewprojection = m_projectionmatrix * m_viewmatrix;
}

glm::mat4 OrthographicCamera::GetProjection() const
{
    return m_projectionmatrix;
}

glm::mat4 OrthographicCamera::GetView() const
{
    return m_viewmatrix;
}

glm::mat4 OrthographicCamera::GetViewProjection() const
{
    return m_viewprojection;
}

void OrthographicCamera::Recalculate()
{
    m_viewmatrix = glm::translate(glm::mat4(1.0f), m_position) *
                   glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    m_viewmatrix = glm::inverse(m_viewmatrix);


    m_viewprojection = m_projectionmatrix * m_viewmatrix;
}
