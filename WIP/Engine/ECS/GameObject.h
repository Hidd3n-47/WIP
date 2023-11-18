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

namespace jci {

// TODO (Christian): look at restriciting the delete method.
class GameObject
{
public:
	~GameObject()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->OnComponentRemove();
			delete m_components[i];
		}
	}

	inline void AddComponent(IComponent* component)
	{
		// Check if it is in the vector, add to vector if not.
		// TODO (Christian): Add a variable to check if the object has a bool by a mask.
		m_components.push_back(component);
		m_components.back()->OnComponentAdd();
	}

	// TODO (Chrisian): Implement this.
	template<class T>
	inline IComponent* GetComponent()
	{
		//try
		//{
		//	// Try get component.
		//}
		//catch
		//{
		//	// The class does not inherit from ICOmponent.
		//	// Assert.
		//}
		return m_components[0];
		return nullptr;
	}
private:
	uint32 m_id;
	//GameObject* m_parent = nullptr;
	//std::vector<GameObject*> m_children; // TODO (Christian): Implement this.
	std::vector<IComponent*> m_components;
};

} // Namespace jci.