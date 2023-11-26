#pragma once

#include "ComponentTypes.h"
#include "ComponentArray.h"

namespace jci {

class Transform;
class SpriteRenderer;
class BoxCollider;

class ComponentManager
{
public:
	inline static ComponentManager* Instance() { return m_instance == nullptr ? m_instance = new ComponentManager() : m_instance; }

	template<class T>
	inline T* AddComponent(ComponentTypes type, T component)
	{
		//m_components[T].AddComponent(component);
		switch (type)
		{
		case ComponentTypes::Transform:
			return m_transformComponents.AddComponent(component);
		case ComponentTypes::SpriteRenderer:
			return m_transformComponents.AddComponent(component);
		case ComponentTypes::BoxCollider:
			return m_transformComponents.AddComponent(component);
		}

		ASSERT(false, "Non-processed component in component manager.");
		return nullptr;
	}


private:
	ComponentManager();
	~ComponentManager();

	static ComponentManager* m_instance;

	//template<class T>
	//std::unordered_map<ComponentTypes, ComponentArray<T>> m_components;
	ComponentArray<Transform> m_transformComponents;
	ComponentArray<SpriteRenderer> m_spriteRcomponents;
	ComponentArray<BoxCollider> m_boxCcomponents;
};

ComponentManager* ComponentManager::m_instance = nullptr;

} // Namespace jci.