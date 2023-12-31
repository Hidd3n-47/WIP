#pragma once

/***
=========================================================================================
WINDOW:
	Engine's window. 
	To create a Window call: Window::Create(WindowProperties);
=========================================================================================
*/
namespace jci {

class Window
{
public:
	inline Window() = default;
	inline ~Window() { Destroy(); }

	static Window* Create(const std::string& title = "Engine", uint16 width = 1280, uint16 height = 720);
	void Update();
	void Destroy();

	// Accessors.
	inline uint16 GetWidth()	const { return m_width; }
	inline uint16 GetHeight()	const { return m_height; }

	// Mutators.
	void Resize(uint16 width, uint16 height);
private:
	Window(const std::string& title = "Engine", uint16 width = 1280, uint16 height = 720);

	// Window Properties.
	std::string		m_title;
	uint16			m_width, m_height;

	// SDL Handle.
	SDL_Window* m_windowHandle;

	void Init();
};

} // Namespace jci.