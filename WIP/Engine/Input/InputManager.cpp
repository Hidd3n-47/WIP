#include "pch.h"
#include "InputManager.h"

#include "src/Engine.h"

namespace jci {

InputManager* InputManager::m_instance = nullptr;

void InputManager::Update()
{
	SDL_Event evnt;
	SDL_PollEvent(&evnt);
	switch (evnt.type)
	{
	case SDL_QUIT:
		Engine::Instance()->StopRunning();
		break;
	case SDL_KEYDOWN:
		InputManager::Instance()->PressKey(evnt.key.keysym.sym);
		break;
	case SDL_KEYUP:
		InputManager::Instance()->ReleaseKey(evnt.key.keysym.sym);
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

bool InputManager::IsKeyPressed(uint16 keyId)
{
	auto it = m_keyMap.find(keyId);

	return it != m_keyMap.end() ? it->second : false;
}

} // Namespace jci.