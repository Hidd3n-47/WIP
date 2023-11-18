#pragma once


class Application
{
public:
	inline static Application* Instance() { return m_instance == nullptr ? m_instance = new Application() : m_instance; }

	void Create();
	void Update();
	inline void Destory() { delete m_instance; }
private:
	Application() = default;
	~Application() = default;

	static Application* m_instance;
};

