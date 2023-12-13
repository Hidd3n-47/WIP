#pragma once
#include "pch.h"

#include "IComponent.h"

/***
=========================================================================================
TRANFORM (COMPONENT):
	Tranform component contains a vector for position and scale.
	// Question: Which direction is the rotation going to be -- add comment.
=========================================================================================
*/
namespace jci {

class Transform : public IComponent
{
public:
	REGISTER_COMPONENT(ComponentTypes::Transform);

	Transform() = default;
	~Transform() = default;

	inline virtual void OnComponentAdd(Entity* entity)	final { m_entity = entity; }
	inline virtual void OnComponentRemove()				final { /* Empty. */ }

	// Accessors.
	/***
	* Get the position of the Transform Component.
	* 
	*/
	inline vec2 GetPosition() const { return m_position; }
	/***
	* Get a pointer position of the Transform Component.
	*
	*/
	inline vec2* GetPositionPointer() { return &m_position; }
	/***
	* Get the scale of the Transform Component.
	*
	*/
	inline vec2 GetScale() const { return m_scale; }
	/***
	* Get the rotation of the Transform Component.
	*
	*/
	inline float GetRotation() const { return m_rotation; }
	/***
	* Get the rotation of the Transform Component.
	*
	*/
	inline float* GetRotationPointer() { return &m_rotation; }

	// Mutators.
	/***
	* Set the position of the Transform Component.
	* 
	*/
	inline void SetPosition(vec2 position) { m_position = position; }
	/***
	* Set the scale of the Transform Component.
	*
	*/
	inline void SetScale(vec2 scale) { m_scale = scale; }
	/***
	* Set the rotation of the Transform Component.
	*
	*/
	inline void SetRotation(float rotation) { m_rotation = rotation; }
	/***
	* Add to the position of the Transform Component.
	*
	*/
	inline void AddToPosition(vec2 addition) { m_position += addition; }

	inline Transform& operator=(Transform& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);
		m_position = std::move(other.m_position);
		m_scale = std::move(other.m_scale);
		m_rotation = std::move(other.m_rotation);

		return *this;
	}
private:
	Entity* m_entity	= nullptr;
	vec2	m_position	= vec2(0.0f);
	vec2	m_scale		= vec2(1.0f);
	float	m_rotation	= 0.0f;
	entId	m_id		= invalid_id;
};

} // Namespace jci