#include "pch.h"
#include "InputManager.h"

InputManager* InputManager::m_instance = nullptr;

bool InputManager::IsKeyPressed(uint16 keyId)
{
	auto it = m_keyMap.find(keyId);

	return it != m_keyMap.end() ? it->second : false;
}
