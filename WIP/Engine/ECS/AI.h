#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Pathfinding/Path.h"

namespace jci {

class NavMesh;

/***
=========================================================================================
AI (COMPONENT):
	AI component will give the attached entity A* pathfinding.
	Note this component will take control of the speed of the entity.
=========================================================================================
*/
class AI : public IComponent
{
public:	
	REGISTER_COMPONENT(ComponentTypes::AI);

	void OnComponentAdd(Entity* entity) final;
	inline void OnComponentRemove() final { }
	
	/***
	* Get the path associated with the AI.
	*
	*/
	inline Path* GetPath() const { return m_path; }
	/***
	* Get the possition of the AI.
	*
	*/
	inline vec2* GetPosition() const { return m_position; }
	/***
	* Get the target position of the AI.
	*
	*/
	inline vec2* GetTargetPosition() const { return m_targetPosition; }
	/***
	* Get the speed of the AI.
	*
	*/
	inline float* GetEntitySpeed() const { return m_entitySpeed; }

	/***
	* Set the path of the AI.
	*
	*/
	inline void SetPath(Path* path) { delete m_path; m_path = path; }
	/***
	* Change the target position of the AI.
	*
	*/
	inline void SetTargetPosition(vec2* position) { m_targetPosition = position; }
	/***
	* Set the speed of the AI.
	*
	*/
	inline void SetEntitySpeed(float* speed) { m_entitySpeed = speed; }

	inline AI& operator=(AI& other) noexcept
	{
		memcpy(this, &other, sizeof(AI));

		return *this;
	}
private:
	Entity* m_entity	= nullptr;
	entId	m_id		= invalid_id;

	NavMesh*	m_mesh				= nullptr;
	Path*		m_path				= nullptr;
	vec2*		m_position			= nullptr;
	vec2*		m_targetPosition	= nullptr;
	float*		m_entitySpeed		= nullptr;
};

} // Namespace jci.