#pragma once
#include "pch.h"

#include "IComponent.h"

namespace jci {

class Path;
class NavMesh;

class AI : public IComponent
{
public:	
	REGISTER_COMPONENT(ComponentTypes::AI);

	void OnComponentAdd(Entity* entity) final;
	inline void OnComponentRemove() final { }
	int i = 0;
	inline Path* GetPath() const { return m_path; }
	inline vec2* GetPosition() const { return m_position; }
	inline vec2* GetTargetPosition() const { return m_targetPosition; }

	inline void SetPath(Path* path) { delete m_path; m_path = path; }
	inline void SetTargetPosition(vec2* position) { m_targetPosition = position; }

	inline AI& operator=(AI& other) noexcept
	{
		m_id = std::move(other.m_id);
		m_entity = std::move(other.m_entity);

		return *this;
	}
private:
	Entity* m_entity;
	entId	m_id = invalid_id;

	NavMesh*	m_mesh				= nullptr;
	Path*		m_path				= nullptr;
	vec2*		m_position			= nullptr;
	vec2*		m_targetPosition	= nullptr;
	// Reference to path.
};

} // Namespace jci.