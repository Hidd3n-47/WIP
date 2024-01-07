/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "InputManager.h"

#include "src/Engine.h"

namespace jci {

InputManager* InputManager::m_instance = nullptr;

void InputManager::Update()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			Engine::Instance()->StopRunning();
			break;
		case SDL_KEYDOWN:
			PressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			ReleaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			PressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			ReleaseKey(evnt.button.button);
			break;
		case SDL_WINDOWEVENT:
			if (evnt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				Engine::Instance()->ResizeWindow(evnt.window.data1, evnt.window.data2);
			}
			break;
		default:
			break;
		}
	}
}

bool InputManager::IsKeyPressed(uint16 keyId)
{
	auto it = m_keyMap.find(keyId);

	return it != m_keyMap.end() ? it->second : false;
}

vec2 InputManager::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return { x, y };
}

} // Namespace jci.