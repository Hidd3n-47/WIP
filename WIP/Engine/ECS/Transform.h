#pragma once

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
	Transform() = default;
	~Transform() = default;

	inline virtual void OnComponentAdd(GameObject* gameObject)	final	{ m_gameObject = gameObject; }
	inline virtual void OnComponentRemove()						final	{ /* Empty. */ }
	
	virtual GameObject* GetGameObject() final { return m_gameObject; }

	inline static uint16 GetIdMask() { return 1 << (int)ComponentTypes::Transform; }

	// Accessors.
	/***
	* Get the position of the Transform Component.
	* 
	*/
	inline vec2 GetPosition() const { return m_position; }
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
private:
	GameObject* m_gameObject	= nullptr;
	vec2 m_position				= vec2(0.0f);
	vec2 m_scale				= vec2(1.0f);
	float m_rotation			= 0.0f;
};

} // Namespace jci