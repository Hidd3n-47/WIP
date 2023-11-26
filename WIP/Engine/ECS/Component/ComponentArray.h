#pragma once
#include "pch.h"

namespace jci {

template <class T>
class ComponentArray
{
public:
	inline ComponentArray()
	{
		m_componentArray = new T[MAX_ENTITIES];
	}

	inline ~ComponentArray()
	{
		delete m_componentArray;
	}

	inline T* AddComponent(T component)
	{
		ASSERT(m_componentIndex < MAX_COMPONENTS, "Maximum components of this type reached.");

		m_componentArray[m_componentIndex] = component;

		return &m_componentArray[m_componentIndex++];
	}
private:
	T* m_componentArray = nullptr;

	entId m_componentIndex = 0;
};

} // Namespace jci.