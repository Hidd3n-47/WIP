#pragma once
#include "pch.h"

#include "IComponent.h"

#include "src/Engine.h"

#include "ComponentManager.h"

namespace jci {

// TODO (Christian): look at restriciting the delete method.
class Entity
{
public:
	Entity(uint16 id) :
		m_id(id)
	{
		DOUT("Created Entity with id: " + std::to_string(m_id));
		AddComponent<Transform>();

	}
	~Entity()
	{
		// Need to remove all the components on entity delete.

		/*for (auto it = m_componentIndices.begin(); it != m_componentIndices.end(); it++)
		{
			ComponentManager::Instance()->RemoveComponent<
		}*/

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

	template<class T>
	inline void RemoveComponent()
	{
		int mask = T::GetIdMask();

		if (!(m_componentMask & mask))
		{
			ASSERT(false, "Game object '" + std::to_string(m_id) + "' does not have component with id: " + std::to_string(mask) + " hence cannot remove it.");
			return;
		}

		entId componentId = m_componentIndices[T::GetType()];

		Entity* ent = ComponentManager::Instance()->RemoveComponent<T>(componentId);

		ent->SetComponentId(T::GetType(), componentId);

		m_componentIndices[T::GetType()] = invalid_id;

		m_componentMask &= (~mask);

		DOUT("Removed component with id: " + T::GetName() + " from Game Object: " + std::to_string(m_id));
	}

	// Accessors.
	inline uint16 GetId() const { return m_id; }
	inline std::string GetTag() const { return m_tag; }

	// Mutators.
	inline void SetTag(const std::string& tag) { m_tag = tag; }
	inline void SetComponentId(ComponentTypes type, entId newId) { m_componentIndices[type] = newId; }
private:
	std::unordered_map<ComponentTypes, entId>	m_componentIndices;

	std::vector<Entity*> m_child; // TODO (Christian): Implement this.
	Entity* m_parent = nullptr;
	uint16 m_id;
	uint16 m_componentMask;

	std::string m_tag = "Untagged";
};

} // Namespace jci.