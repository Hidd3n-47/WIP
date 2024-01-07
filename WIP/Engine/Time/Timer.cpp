/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "Timer.h"

#include "Time.h"

namespace jci {

Timer::Timer(float time, bool repeat /* = false */) :
	m_time(time),
	m_timeRemaining(time),
	m_repeat(repeat)
{
	// Empty.
}

TimerStatus Timer::TimerTick()
{
	m_timeRemaining -= Time::Instance()->GetDeltaTime();

	if (m_timeRemaining <= 0.0f)
	{
		m_timeRemaining = (m_repeat ? m_time : 0.0f);
		return (m_repeat ? TimerStatus::TimeElapsed : TimerStatus::TimerCompleted);
	}

	return TimerStatus::Ticking;
}

bool Timer::TimerTick(float dt)
{
	m_timeRemaining -= dt;

	if (m_timeRemaining <= 0.0f)
	{
		m_timeRemaining = (m_repeat ? m_time : 0.0f);
		return true;
	}

	return false;
}
} // Namespace jci.