#pragma once

#include "Camera/Camera.h"
#include "ECS/GameObject.h"
/***
=========================================================================================
SCENE:
	A collection of GameObjects together to make a level.
	Scene's can only have 1 main orthographic camera.
=========================================================================================
*/
namespace jci {

class GameObject;

class Scene
{
	friend class SceneManager;
public:
	Scene(const std::string& name, uint16 id);
	~Scene();

	GameObject* CreateEmptyGameObject();

	void Update();

	// Accessors.
	/***
	* Returns the name of the scene.
	* 
	*/
	inline std::string GetName() const { return m_name; }
	/***
	* Returns the unique ID of the scene.
	* 
	*/
	inline uint16 GetId() const { return m_id; }
	/***
	* Get a pointer to the orthographic camera of the scene.
	* Will never return null as every scene need's a Camera.
	*/
	inline Camera* GetCamera() const { return m_camera; };
private:
	std::string m_name;
	uint16 m_id;
	uint16 m_gameObjectIndex = 0;
	std::vector<GameObject*> m_gameObjects;
	Camera* m_camera;
};

} // Namespace jci.