#pragma once

#include "ECS/AnchorPoints.h"

namespace jci {

class Camera;

class ButtonManager
{
public:
	inline static ButtonManager* Instance() { return !m_instance ? m_instance = new ButtonManager() : m_instance; }

	void Update();

	vec2 GetAnchorPosition(AnchorPoints anchor);

	inline void SetScreenDimensions(uint16 width, uint16 height) { m_screenWidth = width; m_screenHeight = height; }

	inline void SetCamera(Camera* camera) { m_camera = camera; }
private:
	ButtonManager() = default;
	~ButtonManager() = default;

	static ButtonManager* m_instance;

	uint16 m_screenWidth = -1;
	uint16 m_screenHeight = -1;

	Camera* m_camera;
};

} // Namespace jci.