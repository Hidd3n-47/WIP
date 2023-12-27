#pragma once

namespace jci {

// TODO (Christian): Update the camera matrix when the screen is re-sized.
class Camera
{
public:
	Camera(float left, float right, float top, float bottom);
	~Camera() { }

	void Update();

	// Accessors.
	/***
	* Get the Projection Matrix of the Camera.
	* 
	*/
	const inline mat4&	GetProjMat() const { return m_projMat; }
	/***
	* Get the View Matrix of the Camera.
	*
	*/
	const inline mat4&	GetViewMat() const { return m_viewMat; }
	/***
	* Get the View Projection Matrix of the Camera.
	*	ViewProj = ProjMat * ViewMat
	*/
	const inline mat4&	GetViewProjMat() const { return m_viewProjMat; }
	/***
	* Get the half extends of the camera width and height.
	*	
	*/
	const inline vec2 GetHalfExtents() const { return m_halfExtents; }

	/***
	* Get the position of the camera.
	*
	*/
	inline vec2	GetPosition() const { return m_position; }
	/***
	* Get the rotation of the camera.
	* Note: Rotation in the z-axis.
	*/
	inline float GetRotation() const { return m_rotation; }

	// Mutators.
	/***
	* Set the rotation of the camera.
	* Note: Rotation in the z-axis.
	*/
	inline void SetRotation(float rotation)	{ m_rotation = rotation; RecalculateViewMatrix(); }
	/***
	* Set the position of the camera.
	*
	*/
	inline void SetPosition(vec2 position) { m_position = position; RecalculateViewMatrix(); }
	/***
	* Make the camera follow a position.
	*
	*/
	inline void SetFollowPosition(vec2* position) { m_followPosition = position; }
private:
	mat4	m_projMat;
	mat4	m_viewMat;
	mat4	m_viewProjMat;
	vec2	m_halfExtents;

	vec2	m_position = glm::vec2(0.0f);
	float	m_rotation = 0.0f; // Rotation about the z-axis.

	vec2*	m_followPosition = nullptr;

	void RecalculateViewMatrix();
};

} // Namespace jci.