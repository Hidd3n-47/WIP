#pragma once

#include "Window/Window.h"

/***
=========================================================================================
ENGINE:
	The main engine starting point.
	Initialise, run and destroy the engine.
=========================================================================================
*/
class Engine
{
public:
	inline static Engine* Instance() { return m_instance == nullptr ? m_instance = new Engine() : m_instance; }

	void Init();

	void Run();

	void Destroy();

	inline void StopRunning() { m_running = false; }
private:
	Engine() = default; 
	~Engine() { /* Empty. */ }

	static Engine* m_instance;

	std::unique_ptr<Window> m_window;

	bool m_running = true;
};
