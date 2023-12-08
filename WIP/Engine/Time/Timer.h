#pragma once

namespace jci {

/***
=========================================================================================
TIME_STATUS:
	Status of the timer.
		- Ticking			Timer is ticking down, i.e. is not completed.
		- TimeElapsed		Timer is repeating and has finished a cycle of time.
		- TimerCompleted	Timer is not repeating and finished its time.
=========================================================================================
*/
enum class TimerStatus
{
	Ticking,		// Timer is ticking down, i.e. is not completed.
	TimeElapsed,	// Timer is repeating and has finished a cycle of time.
	TimerCompleted	// Timer is not repeating and finished its time.
};

/***
=========================================================================================
TIME:
	Class to deal with the time of the engine and handle fps capping.
=========================================================================================
*/
class Timer
{
public:
	/***
	* Create a timer that lasts for 'time' seconds.
	* If you would like the timer to repeat ever 'time' seconds, set repeat to true.
	*/
	Timer(float time, bool repeat = false);
	~Timer() = default;

	/***
	* Update the timer. 
	* Returns True when timer has/is completed, and false if not.
	*/
	TimerStatus TimerTick();
	/***
	* Update the timer.
	* Returns True when timer has/is completed, and false if not.
	*/
	bool TimerTick(float dt);

private:
	const float		m_time;
	float			m_timeRemaining;
	bool			m_repeat;
};

} // Namespace