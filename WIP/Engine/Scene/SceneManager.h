#pragma once

#include "Scene.h"

#include "UI/UiManager.h"

/***
=========================================================================================
SCENE_MANAGER:
	Handles the engine's different scenes.
	- Creates new scenes.
	- Deletes scenes (i.e. this manager handles ownership of scenes)
	- Gets scenes.
	- Re-name scenes.
	- Can have a total of 65,535 scenes created.
	Use the Destroy() method to clean up memory.
=========================================================================================
*/
namespace jci {

class SceneManager
{
public:
	inline static SceneManager* Instance() { return m_instance == nullptr ? m_instance = new SceneManager() : m_instance; }

	/***
	* Create a new Scene for the engine.
	* Returns a pointer to the Scene.
	*/
	Scene* CreateScene(const std::string& name);
	/***
	* Destroys and deletes the scene with the passed in name.
	* Asserts if no scene with passed in name.
	*/
	void DestroyScene(const std::string& name);
	/***
	* Destroys and deletes the scene with the passed in id.
	* Asserts if no scene with passed in name.
	*/
	void DestoryScene(uint16 id);
	/***
	* Call the Update method on the currently active Scene.
	*
	*/
	Camera* UpdateCurrentScene(float dt);
	
	// Accessors.
	/***
	* Gets a scene by the passed in name.
	* Asserts and returns null if no scene with passed in name.
	*/
	Scene* GetScene(const std::string& name);
	/***
	* Gets a scene by the passed in id.
	* Asserts and returns null if no scene with passed in id.
	*/
	Scene* GetScene(uint16 id);
	/***
	* Gets the currently active scene.
	* Returns nullptr if there is no currently active scene.
	*/
	inline Scene* GetCurrentScene() const { return m_currentScene; }

	// Mutator.
	/***
	* Re-names the scene with the passed in name to the new passed in name.
	* Asserts if no scene with passed in name.
	*/
	void SetSceneName(const std::string& oldName, const std::string& newName);
	/***
	* Re-names the scene with the passed in id to the new passed in name.
	* Asserts if no scene with passed in id.
	*/
	void SetSceneName(uint16 id, const std::string newName);
	/***
	* Sets the currently active scene.
	*
	*/
	void SetCurrentScene(Scene* scene);

	void Destory();
private:
	SceneManager() = default;
	~SceneManager();

	static SceneManager* m_instance;

	uint16 m_sceneId = 0;
	std::unordered_map<uint16, Scene*> m_scenes;
	Scene* m_currentScene = nullptr;
};

} // Namespace jci.