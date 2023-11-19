#pragma once

// Question (Christian): Should input manager be singleton? if so multi-threadding?
/***
=========================================================================================
INPUT_MANAGER:
	Handles the engine's input.
	Use the Destroy() method to clean up memory.
=========================================================================================
*/
namespace jci {

class InputManager
{
public:
	inline static InputManager* Instance() { return m_instance == nullptr ? m_instance = new InputManager() : m_instance; }

	void Update();

	inline void PressKey(uint16 keyId) { m_keyMap[keyId] = true; }
	inline void ReleaseKey(uint16 keyId) { m_keyMap[keyId] = false; }

	bool IsKeyPressed(uint16 keyId);

	inline void Destroy() { delete m_instance; }
private:
	inline InputManager() { /* Empty. */ }
	inline ~InputManager() { /* Empty. */ }

	static InputManager* m_instance;

	std::unordered_map<uint16, bool> m_keyMap;
};

} // Namespace jci.