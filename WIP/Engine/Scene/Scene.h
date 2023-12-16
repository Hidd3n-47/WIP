#pragma once

#include "Camera/Camera.h"
#include "ECS/Entity.h"
/***
=========================================================================================
SCENE:
	A collection of Entitys together to make a level.
	Scene's can only have 1 main orthographic camera.
=========================================================================================
*/
namespace jci {

class Entity;

class Scene
{
	friend class SceneManager;
public:
	Scene(const std::string& name, uint16 id);
	~Scene();

	/***
	* Returns a pointer to a new entity.
	*
	*/
	Entity* CreateEmptyEntity();

	/***
	* Destroys the passed in entity.
	*
	*/
	void RemoveEnity(Entity* entity);

	/***
	* Update the scenes camera.
	*
	*/
	inline void Update(float dt) { m_camera->Update(); }

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
	uint16 m_entityIndex = 0;
	std::vector<Entity*> m_entities;
	Camera* m_camera;
};

} // Namespace jci.