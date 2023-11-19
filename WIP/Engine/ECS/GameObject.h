#pragma once
#include "pch.h"

//using GameObject = uint32;
//
//const uint32 generationBits = 12;
//const uint32 indexBits = sizeof(GameObject) * 8 - generationBits;
//
//const uint32 indexMask = (1 << indexBits) - 1; // 1,048,576 gameobjects
//const uint32 generationMask = (1 << generationBits) - 1; // 4,096 generations
//const uint32 invalidId = 1;
//
//inline bool isValid(GameObject id)
//{
//	return id != invalidId;
//}
//
//inline GameObject generation(GameObject id)
//{
//	return (id >> indexBits) & generationMask;
//}
//
//inline GameObject newGeneration(GameObject id)
//{
//	const GameObject generation(generation(id) + 1);
//	ASSERT(generation < pow(2, generationBits) - 1, "");
//	return id | (generation << indexBits);
//}

#include "IComponent.h"

#include "Transform.h"

namespace jci {

// TODO (Christian): look at restriciting the delete method.
class GameObject
{
public:
	GameObject(uint16 id) :
		m_id(id)
	{
		DLOG("Created GameObject with id: " + std::to_string(m_id));
		AddComponent<Transform>();

	}
	~GameObject()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			IComponent* comp = m_components[i];
			comp->OnComponentRemove();
			delete comp;
			comp = nullptr;
			DLOG("Removed component from Game Object: " + std::to_string(m_id) + " [Deleted: " + std::to_string(i + 1) + "]");
		}

		DLOG("Destroyed GameObject with id: " + std::to_string(m_id));
	}

	template<class T>
	inline T* AddComponent()
	{
		// TODO (Christian): make this more efficient.
		int mask;
		try
		{
			mask = T::GetIdMask();
		}
		catch (int)
		{
			ASSERT(false, "Invalid type passed in, type must be a Component and have a static GetIdMask method.");
		}
		
		if ((m_componentMask & mask) != 0)
		{
			DLOG("Game object '" + std::to_string(m_id) + "' already has component with id: " + std::to_string(mask));
			return GetComponent<T>();
		}

		T* comp = new T();
		m_components.push_back(comp);
		comp->OnComponentAdd(this);

		m_componentMask |= mask;

		DLOG("Added component with id: " + T::GetName() + " to Game Object: " + std::to_string(m_id) + " [Total: " + std::to_string(m_components.size()) + "]");

		return comp;
	}

	// TODO (Chrisian): Improve efficiency of this.
	template<class T>
	inline T* GetComponent()
	{
		int mask;
		try
		{
			mask = T::GetIdMask();
		}
		catch (int)
		{
			ASSERT(false, "Invalid type passed in, type must be a Component and have a static GetIdMask method.");
		}

		if (!(m_componentMask & mask))
		{
			return nullptr;
		}

		for (int i = 0; i < m_components.size(); i++)
		{
			if (dynamic_cast<T*>(m_components[i]) != nullptr)
			{
				return (T*)m_components[i];
			}
		}

		ASSERT(false, "Component not found in vector, however mask states it should be included.");
		return nullptr;
	}

	template<class T>
	inline void RemoveComponent()
	{
		// TODO (Christian): make this more efficient.
		int mask;
		try
		{
			mask = T::GetIdMask();
		}
		catch (int)
		{
			ASSERT(false, "Invalid type passed in, type must be a Component and have a static GetIdMask method.");
		}

		if (!(m_componentMask & mask))
		{
			ASSERT(false, "Game object '" + std::to_string(m_id) + "' does not have component with id: " + std::to_string(mask) + " hence cannot remove it.");
			return;
		}

		T* comp = new T();
		m_components.push_back(comp);
		comp->OnComponentAdd();

		std::vector<IComponent*>::iterator it = m_components.begin();
		for (int i = 0; i < m_components.size(); i++, it++)
		{
			if (dynamic_cast<T*>(m_components[i]) == nullptr)
			{
				continue;
			}

			delete m_components[i];
			break;
		}
		m_components.erase(it);

		m_componentMask &= (~mask);

		DLOG("Removed component with id: " + T::GetName() + " from Game Object: " + std::to_string(m_id) + " [Total: " + std::to_string(m_components.size()) + "]");
	}

	// Accessors.
	inline uint16 GetId() const { return m_id; }
private:
	std::vector<IComponent*> m_components;
	std::vector<GameObject*> m_children; // TODO (Christian): Implement this.
	GameObject* m_parent = nullptr;
	uint16 m_id;
	uint16 m_componentMask;
};

} // Namespace jci.