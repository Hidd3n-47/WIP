#include "pch.h"
#include "Engine.h"

#include "Input/InputManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/RendererManager.h"
#include "Scene/SceneManager.h"

#include "ECS/GameObject.h"
#include "ECS/SpriteRenderer.h"

#include "Game/src/Application.h"

namespace jci {

Engine* Engine::m_instance = nullptr;

void Engine::Init()
{
	int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
	ASSERT(sdlInit == 0, "Failed to initialise SDL.");

	m_window = std::unique_ptr<Window>(Window::Create());

	Renderer::Init();

	SceneManager::Instance()->SetCurrentScene(SceneManager::Instance()->CreateScene("MainScene"));

	Application::Instance()->Create();

	DLOG("OpenGL Info:");
	DLOG("  Vendor: ");
#ifdef _DEBUG
	std::cout << glGetString(GL_VENDOR) << std::endl;
#endif
	DLOG("  Renderer: ");
#ifdef _DEBUG
	std::cout << glGetString(GL_RENDERER) << std::endl;
#endif
	DLOG("  Version: ");
#ifdef _DEBUG
	std::cout << glGetString(GL_VERSION) << std::endl;
#endif

	uint32 glInit = glewInit();
	ASSERT(glInit == 0, "Failed to initialise OpenGL. Error Code: " + std::to_string(glInit));
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::Run()
{
	GameObject* g = SceneManager::Instance()->CreateEmptyGameObject();
	GameObject* o = SceneManager::Instance()->CreateEmptyGameObject();
	//g->AddComponent(new SpriteRenderer());
	//o->AddComponent(new SpriteRenderer());
	//SpriteRenderer* sr = (SpriteRenderer*)(o->GetComponent<SpriteRenderer>());
	//sr->SetColor(vec3(0.5, 0.5, 0.5));
	while (m_running)
	{
		m_window->Update();

		Application::Instance()->Update(); // delta time.

		InputManager::Instance()->Update();

		SceneManager::Instance()->UpdateCurrentScene(); // delta time.

		// Shader update camer uniform.
		//m_shader->UploadUniformMat4("u_orthoProjMatrix", SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetViewProjMat());

		if (InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_w))
		{
			SpriteRenderer* s = (SpriteRenderer*)(g->GetComponent<SpriteRenderer>());
			s->SetPosition(s->GetPosition() + vec2(0.0f, 0.05f));
		}
		if (InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_s))
		{
			SpriteRenderer* s = (SpriteRenderer*)(g->GetComponent<SpriteRenderer>());
			s->SetPosition(s->GetPosition() + vec2(0.0f, -0.05f));
		}
		if (InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_a))
		{
			SpriteRenderer* s = (SpriteRenderer*)(g->GetComponent<SpriteRenderer>());
			s->SetPosition(s->GetPosition() + vec2(-0.05f, 0.0f));
		}
		if (InputManager::Instance()->IsKeyPressed(SDL_KeyCode::SDLK_d))
		{
			SpriteRenderer* s = (SpriteRenderer*)(g->GetComponent<SpriteRenderer>());
			s->SetPosition(s->GetPosition() + vec2(0.05f, 0.0f));
		}

		Render();

		AfterUpdate();
	}
}

void Engine::Destroy()
{
	Application::Instance()->Destory();

	InputManager::Instance()->Destory();
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