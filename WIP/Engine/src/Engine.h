#pragma once

#include "Window/Window.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

/***
=========================================================================================
ENGINE:
	The main engine starting point.
	Initialise, run and destroy the engine.
=========================================================================================
*/
namespace jci {

class Scene;

class Engine
{
public:
	inline static Engine* Instance() { return m_instance == nullptr ? m_instance = new Engine() : m_instance; }

	void Init();
	void Run();
	void Destroy();

	// After update is where Game Object's and Components will be removed.
	void AfterUpdate();
	void Render();

	inline void StopRunning() { m_running = false; }
	inline void ResizeWindow(int32 width, int32 height) { m_window->Resize(width, height); }
private:
	Engine() = default;
	~Engine() = default;

	static Engine* m_instance;

	std::unique_ptr<Window> m_window;
	bool m_running = true;
};

} // Namespace jci.