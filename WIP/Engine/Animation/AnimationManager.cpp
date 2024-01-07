/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "AnimationManager.h"

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"

namespace jci {

void AnimationManager::Update()
{
	Animation* animation = ComponentManager::Instance()->GetComponentVector<Animation>();

	for (size_t i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::Animation); i++)
	{
		if (!animation[i].GetEntity()->IsActive())
		{
			continue;
		}

		if (animation[i].m_frameTimer.TimerTick() == TimerStatus::TimeElapsed)
		{
			if (++animation[i].m_animationIndex >= animation[i].m_animationCount)
			{
				animation[i].m_animationIndex = animation[i].m_loop ? animation[i].m_startIndex : animation[i].m_animationCount - 1;
			}

			SpriteRenderer* sr = animation[i].GetEntity()->GetComponent<SpriteRenderer>();
			ASSERT(sr, "Animation component needs a sprite renderer in order to work.");

			sr->CalculateUV(animation[i].m_animationIndex);
		}
	}
}

} // Namespace jci.