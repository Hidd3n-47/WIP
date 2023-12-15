#pragma once

namespace jci {

class AnimationManager
{
public:
	inline static AnimationManager* Instance() { return !m_instance ? m_instance = new AnimationManager() : m_instance; }

	void Update();
private:
	AnimationManager() = default;
	~AnimationManager() = default;

	static AnimationManager* m_instance;

};

} // Namespace jci.