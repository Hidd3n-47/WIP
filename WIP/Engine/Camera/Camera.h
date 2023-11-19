#pragma once

namespace jci {

// TODO (Christian): Update the camera matrix when the screen is re-sized.
class Camera
{
public:
	Camera(float left, float right, float top, float bottom);
	~Camera() { }

	// Accessors.
	const inline mat4& GetProjMat() const { return m_projMat; }
	const inline mat4& GetViewMat() const { return m_viewMat; }
	const inline mat4& GetViewProjMat() const { return m_viewProjMat; }
	inline vec2 GetPosition() const { return m_position; }
	inline float GetRotation() const { return m_rotation; }

	// Mutators.
	inline void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
	inline void SetPosition(vec2 position) { m_position = position; RecalculateViewMatrix(); }
private:
	mat4 m_projMat;
	mat4 m_viewMat;
	mat4 m_viewProjMat;
	vec2 m_position = glm::vec2(0.0f); // Quesiton (Christian): does this have to be a vec3?
	float m_rotation = 0.0f; // Rotation about the z-axis.

	void RecalculateViewMatrix();
};

} // Namespace jci.