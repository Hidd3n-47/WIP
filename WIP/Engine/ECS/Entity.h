/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "pch.h"

#include "IComponent.h"

#include "ComponentManager.h"
#include "Scene/SceneManager.h"

namespace jci {

/***
=========================================================================================
ENTITY (Entity):
	Abstract object that exists in a scene.
	Entities have components which can be attached to give it behaviours.
=========================================================================================
*/
class Entity
{
public:
	Entity() = default;
	inline Entity(Scene* scene, uint16 id) :
		m_scene(scene),
		m_id(id)
	{
		DOUT("Created Entity with id: " + std::to_string(m_id));
		AddComponent<Transform>();

	}

	inline ~Entity() = default;

	/***
	* Remove all the components off the entity.
	*
	*/
	inline void RemoveAllComponents()
	{
		for (auto it = m_componentIndices.begin(); it != m_componentIndices.end(); it++)
		{
			Entity* e = ComponentManager::Instance()->RemoveComponent(it->first, it->second);
			if (e)
			{
				e->SetComponentId(it->first, it->second);
			}
		}

		DOUT("Destroyed Entity with id: " + std::to_string(m_id));
	}

	/***
	* Add a component to the entity.
	*
	*/
	template<class T>
	inline T* AddComponent()
	{
		int mask = T::GetIdMask();
		
		if ((m_componentMask & mask) != 0)
		{
			DOUT("Game object '" + std::to_string(m_id) + "' already has component with id: " + std::to_string(mask));
			return GetComponent<T>();
		}

		T* comp = ComponentManager::Instance()->AddComponent<T>();
		comp->OnComponentAdd(this);
		m_componentIndices[T::GetType()] = comp->GetId();

		m_componentMask |= mask;

		DOUT("Added component with id: " + T::GetName() + " to Game Object: " + std::to_string(m_id));

		return comp;
	}

	/***
	* Get the specified component.
	* Returns nullptr if the component is not attached to the entity.
	*/
	template<class T>
	inline T* GetComponent()
	{
		ASSERT(m_id != invalid_id, "Entity has been marked with invalid id and is still trying to be accessed.");
		int mask = T::GetIdMask();

		if (!(m_componentMask & mask))
		{
			return nullptr;
		}

		return ComponentManager::Instance()->GetComponent<T>(m_componentIndices[T::GetType()]);

		ASSERT(false, "Component not found in vector, however mask states it should be included.");
		return nullptr;
	}

	/***
	* Set if the entity is active or not.
	* If it is inactive, none of the components will affect the entity.
	*/
	inline void SetActive(bool active) 
	{ 
		ASSERT(m_scene == SceneManager::Instance()->GetCurrentScene(), "Trying to change an entity to active/inactive in a different scene");
		m_active = active; 
	}

	/***
	* Cache the entity when changing scenes.
	* For internal use.
	*/
	inline void CacheEntity()
	{
		m_cachedEntityActive = m_active;
		m_active = false;
	}
	/***
	* Retriving the cached entity when making scene active.
	* For internal use.
	*/
	inline void RetrieveEntity()
	{
		m_active = m_cachedEntityActive;
	}

	/***
	* Flag if the entity should be destroyed.
	* Note: Destruction occures at the end of the frame.
	*/
	inline void DestoryEntity() { Engine::Instance()->DestroyEntity(this); }
	
	inline Scene* GetScene() const { return m_scene; }

	// Accessors.
	/***
	* Get the ID of the entity.
	*
	*/
	inline uint16 GetId() const { return m_id; }
	/***
	* Get the tag of the entity.
	* Note: Tags might not be unique, i.e. its not a unique identifier.
	*/ 
	inline std::string GetTag() const { return m_tag; }
	/***
	* Get if the entity is active or inactive.
	*
	*/
	inline bool IsActive() const { return m_active; }

	// Mutators.
	/***
	* Set the tag of the entity.
	* Note: Tags might not be unique, i.e. it's not a unique identifier.
	*/
	inline void SetTag(const std::string& tag) { m_tag = tag; }
	/***
	* Set the id of an entity.
	* For internal use.
	*/
	inline void SetId(entId id) { m_id = id; }
	
	inline Entity& operator=(Entity& other) noexcept
	{
		memcpy(this, &other, sizeof(Entity));

		return *this;
	}
private:
	std::unordered_map<ComponentTypes, entId>	m_componentIndices;

	inline void SetComponentId(ComponentTypes type, entId newId) { m_componentIndices[type] = newId; }

	Scene* m_scene  = nullptr;
	entId m_id		= invalid_id;

	uint16 m_componentMask  = 0;
	bool m_active			= true;

	std::string m_tag = "Untagged";

	bool m_cachedEntityActive = true;
};

} // Namespace jci.