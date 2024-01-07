/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once

#include "InputKeyCodes.h"

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

	/***
	* Polls for input and adds to hash map if pressed.
	* 
	*/
	void Update();

	/***
	* Check if a key/button is pressed. True on Key being held down.
	* Can check for mouse as well as keyboard key.
	*/
	bool IsKeyPressed(uint16 keyId);

	/***
	* Get the current screen cooridinates of the mouse position.
	* 
	*/
	vec2 GetMousePosition();

	inline void Destroy() { delete m_instance; }
private:
	inline InputManager()	= default;
	inline ~InputManager()	= default;

	static InputManager* m_instance;

	std::unordered_map<uint16, bool> m_keyMap;
	std::unordered_map<uint8_t, bool> m_mouseMap;

	inline void PressKey(uint16 keyId)		{ m_keyMap[keyId] = true; }
	inline void ReleaseKey(uint16 keyId)	{ m_keyMap[keyId] = false; }
};

} // Namespace jci.