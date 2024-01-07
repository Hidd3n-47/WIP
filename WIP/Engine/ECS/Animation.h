/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "IComponent.h"

#include "Time/Timer.h"

namespace jci {

/***
=========================================================================================
ANIMATION (COMPONENT):
	Animation component will play a sequence of sprites from a sprite sheet
	at a given speed.
	Note: 
		The animation component needs a SpriteRenderer to work.
		The Animation component will take over the SpriteRenderer to ensure the 
		correct texture is displayed.
=========================================================================================
*/
class Animation : public IComponent
{
	friend class AnimationManager;
public:
	REGISTER_COMPONENT(ComponentTypes::Animation);

	inline void OnComponentAdd(Entity* entity) final { m_entity = entity; }
	inline void OnComponentRemove() final { }

	/***
	* Get number of frames in the animation.
	*
	*/
	inline uint32 GetAnimationIndex() const { return m_animationCount; }
	/***
	* Get the starting index of the animation.
	* This is the index that animation starts at in the spritesheet.
	*/
	inline uint32 GetStartIndex() const { return m_startIndex; }

	/***
	* Set if the animation loops or not.
	* If the animation does not loop, it will display the last frame on completion.
	*/
	inline void SetLooping(bool loop) { m_loop = loop; }
	/***
	* Set the starting index of the animation.
	* The starting index is the first index on the sprite sheet that the animation will start from.
	*/
	inline void SetStartIndex(uint32 index) { m_startIndex = index; }
	/***
	* Set the number of animation frames.
	*
	*/
	inline void SetAnimationCount(uint32 count) { m_animationCount = count; m_animationIndex = m_startIndex; }
	/***
	* Set the time between the frames.
	*
	*/
	inline void SetTimeBetweenFrames(float time) { m_frameTimer.SetTime(time); }

	inline Animation& operator=(Animation& other) noexcept
	{
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