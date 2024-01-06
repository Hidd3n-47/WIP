#pragma once
#include "pch.h"

#include "IComponent.h"

#include "ComponentManager.h"
#include "Scene/SceneManager.h"

namespace jci {

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

	inline void SetActive(bool active) 
	{ 
		ASSERT(m_scene == SceneManager::Instance()->GetCurrentScene(), "Trying to change an entity to active/inactive in a different scene");
		m_active = active; 
	}

	inline void CacheEntity()
	{
		m_cachedEntityActive = m_active;
		m_active = false;
	}

	inline void RetrieveEntity()
	{
		m_active = m_cachedEntityActive;
	}

	inline void DestoryEntity() { Engine::Instance()->DestroyEntity(this); }
	
	inline Scene* GetScene() const { return m_scene; }

	// Accessors.
	inline uint16 GetId() const { return m_id; }
	inline std::string GetTag() const { return m_tag; }
	inline bool IsActive() const { return m_active; }
	inline bool* GetActivePointer() { return &m_active; }

	// Mutators.
	inline void SetTag(const std::string& tag) { m_tag = tag; }
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