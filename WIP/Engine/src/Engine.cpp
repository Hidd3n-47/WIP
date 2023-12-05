#include "pch.h"
#include "Engine.h"

#include "Time/Time.h"
#include "IO/IOManager.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Renderer/Renderer.h"
#include "Collision/CollisionManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Renderer/RendererManager.h"

#include "Game/src/Application.h"

namespace jci {

Engine* Engine::m_instance = nullptr;

void Engine::Init()
{
	int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
	ASSERT(sdlInit == 0, "Failed to initialise SDL.");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	m_window = std::unique_ptr<Window>(Window::Create());

#ifdef _DEBUG
	std::cout << std::endl;
	DLOG("================================================================");
	DLOG("OpenGL Info:");
	DLOG("  Vendor: ");
	std::cout << glGetString(GL_VENDOR) << std::endl;
	DLOG("  Renderer: ");
	std::cout << glGetString(GL_RENDERER) << std::endl;
	DLOG("  Version: ");
	std::cout << glGetString(GL_VERSION) << std::endl;
	DLOG("================================================================");
	std::cout << std::endl;
#endif

	SceneManager::Instance()->SetCurrentScene(SceneManager::Instance()->CreateScene("MainScene"));

	TextureManager::Instance()->Init();

	uint32 glInit = glewInit();
	ASSERT(glInit == 0, "Failed to initialise OpenGL. Error Code: " + std::to_string(glInit));

	ASSERT(!SDL_GL_SetSwapInterval(0), "Failed to turn off VSYNC.");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RendererManager::Instance()->Init();

	Application::Instance()->Create();
}

void Engine::Run()
{
	while (m_running)
	{
		float dt = Time::Instance()->Tick();

		m_window->Update();

		RendererManager::Instance()->Begin();

		InputManager::Instance()->Update();

		SceneManager::Instance()->UpdateCurrentScene(dt);

		Application::Instance()->Update(dt);

		CollisionManager::Instance()->Update(dt); // Question: Is dt needed in collision Manager?

		AfterUpdate();

		Render();
	}
}

void Engine::Destroy()
{
	Application::Instance()->Destroy();

	InputManager::Instance()->Destroy();

	CollisionManager::Instance()->Destroy();

	SceneManager::Instance()->Destory();

	RendererManager::Instance()->Destroy();
	Renderer::Destroy();

	m_window->Destroy();

	SDL_Quit();

	DOUT_CLOSE();

	delete m_instance;
}

void Engine::AfterUpdate()
{
	// TODO (Christian): Delete game objects here.
}

void Engine::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RendererManager::Instance()->End();
}

} // Namespace jci.