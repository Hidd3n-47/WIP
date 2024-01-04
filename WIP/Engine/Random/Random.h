#pragma once

namespace jci {

class Random
{
public:
	inline static Random* Instance() { return !m_instance ? m_instance = new Random() : m_instance; }

	void Init();
	inline void Destroy() { delete m_instance; }
	/***
	* Get a random number between 0.0f and 1.0f.
	* 
	*/
	float Rand();
private:
	Random() = default;
	~Random() = default;

	static Random* m_instance;

	std::mt19937 m_randomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> m_distribution;
};

}