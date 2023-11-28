#include "pch.h"
#include "Time.h"

namespace jci {

Time* Time::m_instance = nullptr;

float Time::Tick()
{
	uint32 now = SDL_GetTicks();
	m_deltaTime = (now - m_lastTime) / 1000.0f;

	if (m_targetFrameTime > m_deltaTime)
	{
		SDL_Delay((m_targetFrameTime - m_deltaTime) * 1000.0f);
		m_deltaTime = m_targetFrameTime;
	}

	m_lastTime = now;

	return m_deltaTime;
}

} // Namespace jci.