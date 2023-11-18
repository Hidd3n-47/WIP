#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace jci {

Camera::Camera(float left, float right, float top, float bottom) :
	m_projMat(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
	m_viewMat(1.0f)
{
	m_viewProjMat = m_projMat * m_viewMat;
}

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(mat4(1.0f), vec3(m_position, 0.0f)) * glm::rotate(mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_viewMat = glm::inverse(transform);
	m_viewProjMat = m_projMat * m_viewMat;
}

} // Namespace jci.