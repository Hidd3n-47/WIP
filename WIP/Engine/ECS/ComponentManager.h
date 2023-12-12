#pragma once

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "NavBlock.h"
#include "AI.h"

namespace jci {

class Entity;

template<class T>
struct ComponentVector
{
	ComponentVector(T* vector, entId numberOfElements) : m_vector(vector), numberOfElements(numberOfElements) { /* Empty. */ }
	entId numberOfElements;

	inline T& operator[] (int index)
	{
		ASSERT(index <= numberOfElements, "Out of bounds.");
		return m_vector[numberOfElements];
	}
private:
	T* m_vector;
};

class ComponentManager
{
public:
	inline static ComponentManager* Instance() { return m_instance == nullptr ? m_instance = new ComponentManager() : m_instance; }

	void Init();

	template<class ComponentClass>
	inline ComponentClass* RegisterComponent(ComponentTypes type, std::vector<ComponentClass>& componentVector)
	{
		entId componentIndex = m_componentIndices[(entId)type]++;

		ComponentClass comp;
		comp.SetId(componentIndex);
		componentVector[componentIndex] = comp;
		return &componentVector[componentIndex];
	}

	template<class T>
	inline T* AddComponent()
	{
		ASSERT(false, "Unhandled component added.");
		return nullptr;
	}

	template<>
	inline Transform* AddComponent<Transform>()
	{
		return RegisterComponent(ComponentTypes::Transform, m_transforms);
	}

	template<>
	inline SpriteRenderer* AddComponent<SpriteRenderer>()
	{
		return RegisterComponent(ComponentTypes::SpriteRenderer, m_spriteRenderers);
	}

	template<>
	inline BoxCollider* AddComponent<BoxCollider>()
	{
		return RegisterComponent(ComponentTypes::BoxCollider, m_boxColliders);
	}

	template<>
	inline NavBlock* AddComponent<NavBlock>()
	{
		return RegisterComponent(ComponentTypes::NavBlock, m_navBlocks);
	}

	template<>
	inline AI* AddComponent<AI>()
	{
		return RegisterComponent(ComponentTypes::AI, m_ais);
	}

	template<class ComponentClass>
	inline ComponentClass* RetrieveComponent(std::vector<ComponentClass>& componetVector, entId componentId)
	{
		if (componetVector[componentId].GetId() == invalid_id)
		{
			ASSERT(false, "Component has invalid argument whilst existing.");
			return nullptr;
		}

		return &componetVector[componentId];
	}

	template<class T>
	inline T* GetComponent(entId componentId)
	{
		ASSERT(false, "Unhandled component added.");
		return nullptr;
	}

	template<>
	inline Transform* GetComponent<Transform>(entId componentId)
	{
		return RetrieveComponent(m_transforms, componentId);
	}

	template<>
	inline SpriteRenderer* GetComponent<SpriteRenderer>(entId componentId)
	{
		return RetrieveComponent(m_spriteRenderers, componentId);
	}

	template<>
	inline BoxCollider* GetComponent<BoxCollider>(entId componentId)
	{
		return RetrieveComponent(m_boxColliders, componentId);
	}

	template<>
	inline NavBlock* GetComponent<NavBlock>(entId componentId)
	{
		return RetrieveComponent(m_navBlocks, componentId);
	}

	template<>
	inline AI* GetComponent<AI>(entId componentId)
	{
		return RetrieveComponent(m_ais, componentId);
	}

	template<class ComponentClass>
	inline Entity* DeregisterComponent(ComponentTypes type, std::vector<ComponentClass>& componentVector, entId id)
	{
		ASSERT(componentVector[id].GetId() != invalid_id, "Component has invalid id whilst existing.");

		m_componentIndices[(entId)type]--;
		componentVector[id] = componentVector.back();
		componentVector.back().SetId(invalid_id);
		return componentVector.back().GetEntity();
	}

	template<class T>
	inline Entity* RemoveComponent(entId id)
	{
		ASSERT(false, "Unhandled component removal.");
	}

	template<>
	inline Entity* RemoveComponent<Transform>(entId id)
	{
		return DeregisterComponent(ComponentTypes::Transform, m_transforms, id);
	}

	template<>
	inline Entity* RemoveComponent<SpriteRenderer>(entId id)
	{
		return DeregisterComponent(ComponentTypes::SpriteRenderer, m_spriteRenderers, id);
	}

	template<>
	inline Entity* RemoveComponent<BoxCollider>(entId id)
	{
		return DeregisterComponent(ComponentTypes::BoxCollider, m_boxColliders, id);
	}

	template<>
	inline Entity* RemoveComponent<NavBlock>(entId id)
	{
		return DeregisterComponent(ComponentTypes::NavBlock, m_navBlocks, id);
	}

	template<>
	inline Entity* RemoveComponent<AI>(entId id)
	{
		return DeregisterComponent(ComponentTypes::AI, m_ais, id);
	}

	template<class T>
	inline T* GetComponentVector()
	{
		ASSERT(false, "Getting the Component Vector has not been implemented.");

		return;
	}

	/*template<>
	inline ComponentVector<Transform> GetComponentVector()
	{ 
		return ComponentVector<Transform>(m_transforms, m_componentIndices[(entId)ComponentTypes::Transform]);
	}

	template<>
	inline ComponentVector<SpriteRenderer> GetComponentVector()
	{ 
		return ComponentVector<SpriteRenderer>(m_spriteRenderers, m_componentIndices[(entId)ComponentTypes::SpriteRenderer]);
	}

	template<>
	inline ComponentVector<BoxCollider> GetComponentVector()
	{ 
		return ComponentVector<BoxCollider>(m_boxColliders, m_componentIndices[(entId)ComponentTypes::BoxCollider]);
	}

	template<>
	inline ComponentVector<NavBlock> GetComponentVector()
	{ 
		return ComponentVector<NavBlock>(m_navBlocks, m_componentIndices[(entId)ComponentTypes::NavBlock]);
	}*/

	template<>
	inline AI* GetComponentVector()
	{
		return &m_ais[0];
	}

	inline entId GetComponentCount(ComponentTypes type) const { return m_componentIndices[(entId)type]; }

	// TODO (Christian) Add a remove component.
private:
	ComponentManager()	= default;
	~ComponentManager()	= default;

	static ComponentManager* m_instance;
	
	std::vector<Transform>		m_transforms;
	std::vector<SpriteRenderer>	m_spriteRenderers;
	std::vector<BoxCollider>	m_boxColliders;
	std::vector<NavBlock>		m_navBlocks;
	std::vector<AI>				m_ais;

	entId	m_componentIndices[(entId)ComponentTypes::Count];

};

} // Namespace jci.