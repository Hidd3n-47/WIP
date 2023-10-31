#include "pch.h"
#include "Window.h"

Window* Window::Create(const WindowProperties& properties)
{
	return new Window(properties);
}

Window::Window(const WindowProperties& properties) :
	m_title(properties.title),
	m_width(properties.width),
	m_height(properties.height)
{
	Init();
}

void Window::Update()
{
	// Update double buffer and poll input.
}

void Window::Destroy()
{
	SDL_DestroyWindow(m_windowHandle);
}

void Window::Init()
{
	// If going to use openGL, dont forget to create opengl methods.
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// If going to use openGL, dont forget to create opengl methods.
	m_windowHandle = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, /*SDL_WINDOW_OPENGL |*/ SDL_WINDOW_RESIZABLE);

	// If going to use openGL, dont forget to create opengl methods.
	//SDL_GLContext glContext = SDL_GL_CreateContext(m_windowHandle);

	DLOG("Created window: " + m_title + " " + std::to_string(m_width) + " x " + std::to_string(m_height));
}