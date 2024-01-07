/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "Window/Window.h"

/***
=========================================================================================
ENGINE:
	The main engine starting point.
	Initialise, run and destroy the engine.
=========================================================================================
*/
namespace jci {

class Scene;
class Shader;
class VertexBuffer;
class VertexArray;
class Entity;

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

	inline uint16 GetScreenWidth() const { return m_window->GetWidth(); }
	inline uint16 GetScreenHeight() const { return m_window->GetHeight(); }

	inline void DestroyEntity(Entity* entity) { m_entsToDestroy.push_back(entity); }

#ifdef _DEBUG
	std::string dout = "Engine Logging:\n\n";
#endif
private:
	Engine() = default;
	~Engine() = default;

	static Engine* m_instance;

	std::unique_ptr<Window> m_window;
	bool m_running = true;

	std::vector<Entity*> m_entsToDestroy;
};

} // Namespace jci.