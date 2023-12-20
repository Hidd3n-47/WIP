#pragma once
#include "pch.h"

#include "IComponent.h"

#include "src/Engine.h"

#include "ComponentManager.h"

namespace jci {

class Scene;

// TODO (Christian): look at restriciting the delete method.
class Entity
{
public:
	inline Entity(Scene* scene, uint16 id) :
		m_scene(scene),
		m_id(id)
	{
		DOUT("Created Entity with id: " + std::to_string(m_id));
		AddComponent<Transform>();

	}

	inline ~Entity()
	{
		for (auto it = m_componentIndices.begin(); it != m_componentIndices.end(); it++)
		{
			ComponentManager::Instance()->RemoveComponent(it->first, it->second);
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
		int mask = T::GetIdMask();

		if (!(m_componentMask & mask))
		{
			return nullptr;
		}

		return ComponentManager::Instance()->GetComponent<T>(m_componentIndices[T::GetType()]);

		ASSERT(false, "Component not found in vector, however mask states it should be included.");
		return nullptr;
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
	inline void SetComponentId(ComponentTypes type, entId newId) { m_componentIndices[type] = newId; }
	inline void SetActive(bool active) { m_active = active; }
private:
	std::unordered_map<ComponentTypes, entId>	m_componentIndices;

	Scene* m_scene = nullptr;
	std::vector<Entity*> m_child; // TODO (Christian): Implement this.
	Entity* m_parent = nullptr;
	uint16 m_id;
	uint16 m_componentMask;
	bool m_active = true;

	std::string m_tag = "Untagged";
};

} // Namespace jci.