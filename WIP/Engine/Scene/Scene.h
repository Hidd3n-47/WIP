#pragma once

#include "Camera/Camera.h"

namespace jci {

class GameObject;

class Scene
{
	friend class SceneManager;
public:
	Scene(const std::string& name, uint16 id);
	~Scene();

	void Update();

	// Accessors.
	inline Camera* GetCamera() const { return m_camera; };

	// Mutators.
	inline void SetCamera(Camera* camera) { m_camera = camera; }
private:
	std::string m_name;
	uint16 m_id;
	std::vector<GameObject*> m_gameObjects;
	Camera* m_camera;
};

} // Namespace jci.