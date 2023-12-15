#include "pch.h"
#include "AnimationManager.h"

#include "ECS/ComponentManager.h"

namespace jci {

AnimationManager* AnimationManager::m_instance = nullptr;

void AnimationManager::Update()
{
	Animation* animation = ComponentManager::Instance()->GetComponentVector<Animation>();

	for (size_t i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::Animation); i++)
	{

		if (animation[i].m_frameTimer.TimerTick() == TimerStatus::TimeElapsed)
		{
			animation[i].m_animationIndex = animation[i].m_animationIndex == animation[i].m_animationCount - 1 ? 0 : animation[i].m_animationIndex + 1;
			animation[i].SetTextureIndex(animation[i].m_animationIndex);
		}
	}
}

} // Namespace jci.