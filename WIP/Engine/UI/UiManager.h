#pragma once

#include "AnchorPoints.h"

namespace jci {

class Camera;

class UiManager
{
public:
	inline static UiManager* Instance() { return !m_instance ? m_instance = new UiManager() : m_instance; }

	inline void Destroy() { delete m_instance; }

	void Update();

	vec2 GetAnchorPosition(AnchorPoints anchor);

	inline void SetScreenDimensions(uint16 width, uint16 height) { m_screenWidth = width; m_screenHeight = height; }

	inline void SetCamera(Camera* camera) { m_camera = camera; }
private:
	UiManager() = default;
	~UiManager() = default;

	static UiManager* m_instance;

	uint16 m_screenWidth = -1;
	uint16 m_screenHeight = -1;

	Camera* m_camera;
};

} // Namespace jci.