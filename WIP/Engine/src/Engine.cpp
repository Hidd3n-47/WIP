#include "pch.h"
#include "Engine.h"

#include "Input/InputManager.h"

Engine* Engine::m_instance = nullptr;

void Engine::Init()
{
	int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);

	ASSERT(sdlInit == 0, "Failed to initialise SDL.");

	m_window = std::unique_ptr<Window>(Window::Create());
}

void Engine::Run()
{
	while (m_running)
	{
		m_window->Update();

		// TODO (Christian): Abstract this code out to be out of the engine file.
		SDL_Event evnt;
		SDL_PollEvent(&evnt);
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			InputManager::Instance()->PressKey(evnt.key.keysym.sym);
			DLOG("pressed");
			break;
		case SDL_KEYUP:
			InputManager::Instance()->ReleaseKey(evnt.key.keysym.sym);
			break;
		case SDL_WINDOWEVENT:
			if (evnt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				m_window->Resize(evnt.window.data1, evnt.window.data2);
			}
			break;
		default:
			break;
		}
	}
}

void Engine::Destroy()
{
	SDL_Quit();

	delete m_instance;
}