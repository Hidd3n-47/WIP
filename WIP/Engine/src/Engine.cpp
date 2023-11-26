#include "pch.h"
#include "Engine.h"

#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "ECS/EntityManager.h"
#include "Renderer/RendererManager.h"
#include "Collision/CollisionManager.h"

#include "ECS/Entity.h"
#include "ECS/Component/SpriteRenderer.h"

#include "Game/src/Application.h"

namespace jci {

Engine* Engine::m_instance = nullptr;

void Engine::Init()
{
	int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
	ASSERT(sdlInit == 0, "Failed to initialise SDL.");

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

	Renderer::Init();

	SceneManager::Instance()->SetCurrentScene(SceneManager::Instance()->CreateScene("MainScene"));

	EntityManager::Instance()->Init();

	Application::Instance()->Create();

	uint32 glInit = glewInit();
	ASSERT(glInit == 0, "Failed to initialise OpenGL. Error Code: " + std::to_string(glInit));
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::Run()
{
	while (m_running)
	{
		m_window->Update();

		InputManager::Instance()->Update();

		SceneManager::Instance()->UpdateCurrentScene(); // delta time.

		Application::Instance()->Update(); // delta time.

		CollisionManager::Instance()->Update();

		AfterUpdate();

		Render(); // Question: should the rendere be before or after the 'AfterUpdate'.
	}
}

void Engine::Destroy()
{
	Application::Instance()->Destroy();

	InputManager::Instance()->Destroy();

	CollisionManager::Instance()->Destroy();

	EntityManager::Instance()->Destoy();

	SceneManager::Instance()->Destory();

	RendererManager::Instance()->Destroy();
	Renderer::Destroy();

	m_window->Destroy();

	SDL_Quit();

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

	RendererManager::Instance()->RenderUpdate();
}

} // Namespace jci.