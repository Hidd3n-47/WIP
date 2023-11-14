#pragma once

/***
=========================================================================================
WINDOW_PROPERTIES:
	Structure holding the properties for a window.
=========================================================================================
*/
struct WindowProperties
{
	WindowProperties(const std::string& title = "Engine", uint16 width = 1280, uint16 height = 720) :
		title(title),
		width(width),
		height(height)
	{
		// Empty.
	}

	std::string title;
	uint16 width, height;
};

/***
=========================================================================================
WINDOW:
	Engine's window. 
	To create a Window call: Window::Create(WindowProperties);
=========================================================================================
*/
class Window
{
public:
	inline Window() = default;
	inline ~Window() { Destroy(); }

	static Window* Create(const WindowProperties& properties = WindowProperties());
	void Update();
	void Destroy();
	
	// Temp
	inline void SetRenderer(SDL_Renderer*& ren) { ren = SDL_CreateRenderer(m_windowHandle, 0, 0); if(ren == nullptr) Log::FatalError("err", ERR_CODE::SDL_ERROR); }

	// Accessors.
	inline uint16 GetWidth()	const { return m_width; }
	inline uint16 GetHeight()	const { return m_height; }

	// Mutators.
	inline void Resize(uint16 width, uint16 height) { m_width = width; m_height = height; DLOG("Window resized to: " + std::to_string(width) + " x " + std::to_string(height)); }

private:
	Window(const WindowProperties& properties = WindowProperties());

	// Window Properties.
	std::string		m_title;
	uint16			m_width, m_height;

	// SDL Handle.
	SDL_Window*		m_windowHandle;

	void Init();
};