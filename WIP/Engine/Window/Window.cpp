#include "pch.h"
#include "Window.h"

#include "Time/Time.h"
#include "UI/ButtonManager.h"

namespace jci {

Window::Window(const std::string& title /* = "Engine" */, uint16 width /* = 1280 */, uint16 height /* = 720 */) :
	m_title(title),
	m_width(width),
	m_height(height)
{
	Init();
}

Window* Window::Create(const std::string& title /* = "Engine" */, uint16 width /* = 1280 */, uint16 height /* = 720 */)
{
	return new Window(title, width, height);
}

void Window::Update()
{
	// TODO (Christian): Swap the buffers.
	SDL_GL_SwapWindow(m_windowHandle);
	SDL_SetWindowTitle(m_windowHandle, ("WIP " + std::to_string(Time::Instance()->GetFps())).c_str());
}

void Window::Destroy()
{
	SDL_DestroyWindow(m_windowHandle);
}


void Window::Resize(uint16 width, uint16 height) 
{ 
	m_width = width; m_height = height; 
	glViewport(0, 0, m_width, m_height); 
	ButtonManager::Instance()->SetScreenDimensions(width, height);
	DLOG("Window resized to: " + std::to_string(width) + " x " + std::to_string(height)); 
}

void Window::Init()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_windowHandle = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	SDL_GLContext glContext = SDL_GL_CreateContext(m_windowHandle);
	ASSERT(glContext != 0, "Failed to create SDL GL Window Context.");

	ButtonManager::Instance()->SetScreenDimensions(m_width, m_height);
	DLOG("Created window: " + m_title + " " + std::to_string(m_width) + " x " + std::to_string(m_height));
}

} // Namespace jci.