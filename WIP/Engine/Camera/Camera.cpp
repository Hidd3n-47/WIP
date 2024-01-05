#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace jci {

Camera::Camera(float left, float right, float top, float bottom) :
	m_projMat(glm::ortho(left, right, bottom, top, -10.0f, 10.0f)),
	m_viewMat(1.0f),
	m_halfExtents(vec2(right, top))
{
	m_viewProjMat = m_projMat * m_viewMat;
}

void Camera::Update()
{
	if (!m_followPosition) { return; }

	vec2 postion = m_position + (*m_followPosition - m_position) * 1.0f / m_followSpeed;

	SetPosition(postion);
}

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(mat4(1.0f), vec3(m_position, 0.0f)) * glm::rotate(mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_viewMat = glm::inverse(transform);
	m_viewProjMat = m_projMat * m_viewMat;
}

} // Namespace jci.