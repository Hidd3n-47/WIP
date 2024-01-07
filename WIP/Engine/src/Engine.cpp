/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "Engine.h"

#include "Time/Time.h"
#include "IO/IOManager.h"
#include "UI/UiManager.h"
#include "Random/Random.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Pathfinding/AIManager.h"
#include "Physics/PhysicsManager.h"
#include "Graphics/Texture/Texture.h"
#include "Collision/CollisionManager.h"
#include "Animation/AnimationManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Renderer/RenderManager.h"
#include "Collision/CollisionCallbackManager.h"

#include "Game/src/Application.h"

#include "Graphics/Renderer/VertexArray.h"
#include "Graphics/Renderer/Shader.h"

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

	uint32 vsyncDisable = SDL_GL_SetSwapInterval(0);
	ASSERT(vsyncDisable == 0, "Failed to turn off VSYNC.");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ComponentManager::Instance()->Init();

	RendererManager::Instance()->Init();

	AudioManager::Instance()->Init();

	Application::Instance()->Create();

	Random::Instance()->Init();
}

void Engine::Run()
{
	while (m_running)
	{
		float dt = Time::Instance()->Tick();

		m_window->Update();

		RendererManager::Instance()->Begin();

		InputManager::Instance()->Update();

		Camera* cam = SceneManager::Instance()->UpdateCurrentScene(dt);

		Application::Instance()->Update(dt);

		AnimationManager::Update();

		PhysicsManager::Update(dt);
		
		CollisionManager::Instance()->Update(m_window->GetWidth(), m_window->GetHeight(), cam->GetPosition());
		
		AIManager::Update(dt);

		UiManager::Instance()->Update();

		AfterUpdate();

		ParticleManager::Instance()->Update(dt);

		Render();
	}
}

void Engine::Destroy()
{
	Random::Instance()->Destroy();

	TextureManager::Instance()->Destory();

	Application::Instance()->Destroy();

	InputManager::Instance()->Destroy();

	CollisionCallbackManager::Instance()->Destroy();
	CollisionManager::Instance()->Destroy();

	SceneManager::Instance()->Destory();

	ComponentManager::Instance()->Destroy();

	UiManager::Instance()->Destroy();

	ParticleManager::Instance()->Destroy();

	PathfindingManager::Instance()->Destroy();

	AudioManager::Instance()->Destroy();

	RendererManager::Instance()->Destroy();

	Time::Instance()->Destroy();

	m_window->Destroy();

	SDL_Quit();

	DOUT_CLOSE();
	IOManager::Instance()->Destroy();

	delete m_instance;
}

void Engine::AfterUpdate()
{
	while (m_entsToDestroy.size())
	{
		Entity* e = m_entsToDestroy.back();

		if (!e || e->GetId() == invalid_id)
		{
			ASSERT(false, "Entity already deleted previously.");
			m_entsToDestroy.pop_back();
		}
		else
		{
			e->GetScene()->RemoveEnity(e);
			m_entsToDestroy.pop_back();
		}
	}
}

void Engine::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RendererManager::Instance()->End();
}

} // Namespace jci.