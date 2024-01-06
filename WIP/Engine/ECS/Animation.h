#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Time/Timer.h"

namespace jci {

class Animation : public IComponent
{
	friend class AnimationManager;
public:
	REGISTER_COMPONENT(ComponentTypes::Animation);

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	inline uint32 GetAnimationIndex() const { return m_animationCount; }
	inline uint32 GetStartIndex() const { return m_startIndex; }

	inline void SetLooping(bool loop) { m_loop = loop; }
	inline void SetStartIndex(uint32 index) { m_startIndex = index; }
	inline void SetAnimationCount(uint32 count) { m_animationCount = count; m_animationIndex = m_startIndex; }
	inline void SetTimeBetweenFrames(float time) { m_frameTimer.SetTime(time); }

	inline Animation& operator=(Animation& other) noexcept
	{
		/*m_entity = other.m_entity;
		m_id = other.m_id;

		m_frameTimer = other.m_frameTimer;
		m_startIndex = other.m_startIndex;
		m_animationIndex = other.m_animationIndex;
		m_animationCount = other.m_animationCount;
		m_loop = other.m_loop;


		return *this; */
		memcpy(this, &other, sizeof(Animation));

		return *this;
	}
private:
	Entity* m_entity	= nullptr;
	entId	m_id		= invalid_id;

	Timer	m_frameTimer		= Timer(0.0f, true);
	uint32	m_startIndex		= 0;
	uint32	m_animationIndex	= 0;
	uint32	m_animationCount	= 1;
	bool	m_loop				= true;
};

} // Namespace jci.