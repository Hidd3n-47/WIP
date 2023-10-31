#pragma once

// Question (Christian): Should input manager be singleton? if so multi-threadding?
/***
=========================================================================================
INPUT_MANAGER:
	Handles the engine's input.
=========================================================================================
*/
class InputManager
{
public:
	inline static InputManager* Instance() { return m_instance == nullptr ? m_instance = new InputManager() : m_instance; }
	//InputManager();
	//~InputManager() { }

	inline void PressKey(uint16 keyId)		{ m_keyMap[keyId] = true; }
	inline void ReleaseKey(uint16 keyId)		{ m_keyMap[keyId] = false; }

	bool IsKeyPressed(uint16 keyId);
private:
	inline InputManager() { /* Empty. */ }
	inline ~InputManager() { delete m_instance; }

	static InputManager* m_instance;

	std::unordered_map<uint16, bool> m_keyMap;
};
