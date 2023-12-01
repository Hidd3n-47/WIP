#pragma once

/***
=========================================================================================
TIME:
	Class to deal with the time of the engine and handle fps capping.
=========================================================================================
*/
namespace jci {

class Time
{
public:
	inline static Time* Instance() { return m_instance == nullptr ? m_instance = new Time() : m_instance; }

	/***
	* Method which calculates delta time and delays engine to meet target fps.
	* Returns delta time.
	*/
	float Tick();

	/***
	* Get the fps at a given frame in time.
	* 
	*/
	inline float GetFps() const { return 1.0f / m_deltaTime; }

	// Accessors.
	/***
	* Get the time between frames in engine update.
	* Measured in ms.
	*/
	inline float GetDeltaTime() const { return m_deltaTime; }

	// Mutators.
	/***
	* Set the max frame rate of the engine.
	*
	*/
	inline void SetMaxFps(float maxFps) { m_maxFps = maxFps; m_targetFrameTime = 1.0f / maxFps; }
private:
	Time() = default;
	inline ~Time() { delete m_instance; }

	static Time* m_instance;

	float	m_maxFps	= 120.0f;
	float	m_deltaTime = 0.0f;
	uint64	m_start		= 0.0f;
	uint64	m_lastTime	= 0.0f;

	float m_targetFrameTime = 1.0f / m_maxFps;
};

} // Namesapce jci.