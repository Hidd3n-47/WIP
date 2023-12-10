#pragma once

#include "ECS/Transform.h"
#include "ECS/SpriteRenderer.h"
#include "ECS/BoxCollider.h"

namespace jci {

class Entity;

class ComponentManager
{
public:
	inline static ComponentManager* Instance() { return m_instance == nullptr ? m_instance = new ComponentManager() : m_instance; }

	void Init();

	// TODO (Christian): See if this can be made better by using copy constructor.
	template<class T>
	inline T* AddComponent()
	{
		ASSERT(false, "Unhandled component added.");
		return nullptr;
	}

	template<>
	inline Transform* AddComponent<Transform>()
	{
		entId componentIndex = m_componentIndices[(entId)ComponentTypes::Transform]++;

		Transform comp;
		comp.SetId(componentIndex);
		m_transforms[componentIndex] = comp;
		return &m_transforms[componentIndex];
	}

	template<>
	inline SpriteRenderer* AddComponent<SpriteRenderer>()
	{
		entId componentIndex = m_componentIndices[(entId)ComponentTypes::SpriteRenderer]++;

		SpriteRenderer comp;
		comp.SetId(componentIndex);
		m_spriteRenderers[componentIndex] = comp;
		return &m_spriteRenderers[componentIndex];
	}

	template<>
	inline BoxCollider* AddComponent<BoxCollider>()
	{
		entId componentIndex = m_componentIndices[(entId)ComponentTypes::BoxCollider]++;

		BoxCollider comp;
		comp.SetId(componentIndex);
		m_boxColliders[componentIndex] = comp;
		return &m_boxColliders[componentIndex];
	}


	template<class T>
	inline T* GetComponent(entId componentId)
	{
		// TODO (Christian): Check that the component is valid.
		ASSERT(false, "Unhandled component added.");
		return nullptr;
	}

	template<>
	inline Transform* GetComponent<Transform>(entId componentId)
	{
		if (m_transforms[componentId].GetId() == invalid_id)
		{
			ASSERT(false, "Component has invalid argument whilst existing.");
			return nullptr;
		}

		return &m_transforms[componentId];
	}

	template<>
	inline SpriteRenderer* GetComponent<SpriteRenderer>(entId componentId)
	{
		if (m_spriteRenderers[componentId].GetId() == invalid_id)
		{
			ASSERT(false, "Component has invalid id whilst existing.");
			return nullptr;
		}

		return &m_spriteRenderers[componentId];
	}

	template<>
	inline BoxCollider* GetComponent<BoxCollider>(entId componentId)
	{
		if (m_boxColliders[componentId].GetId() == invalid_id)
		{
			ASSERT(false, "Component has invalid argument whilst existing.");
			return nullptr;
		}

		return &m_boxColliders[componentId];
	}

	template<class T>
	inline Entity* RemoveComponent(entId id)
	{
		ASSERT(false, "Unhandled component removal.");
	}

	template<>
	inline Entity* RemoveComponent<Transform>(entId id)
	{
		ASSERT(m_transforms[id].GetId() != invalid_id, "Component has invalid id whilst existing.");

		m_componentIndices[(entId)ComponentTypes::Transform]--;
		m_transforms[id] = m_transforms.back();
		m_transforms.back().SetId(invalid_id);
		return m_transforms.back().GetEntity();
	}

	template<>
	inline Entity* RemoveComponent<SpriteRenderer>(entId id)
	{
		ASSERT(m_spriteRenderers[id].GetId() != invalid_id, "Component has invalid id whilst existing.");
		
		m_spriteRenderers.back().OnComponentRemove();

		m_componentIndices[(entId)ComponentTypes::SpriteRenderer]--;
		m_spriteRenderers[id] = m_spriteRenderers.back();
		m_spriteRenderers.back().SetId(invalid_id);
		return m_spriteRenderers.back().GetEntity();
	}

	template<>
	inline Entity* RemoveComponent<BoxCollider>(entId id)
	{
		ASSERT(m_boxColliders[id].GetId() != invalid_id, "Component has invalid id whilst existing.");

		m_boxColliders.back().OnComponentRemove();

		m_componentIndices[(entId)ComponentTypes::BoxCollider]--;
		m_boxColliders[id] = m_boxColliders.back();
		m_boxColliders.back().SetId(invalid_id);
		return m_boxColliders.back().GetEntity();
	}

	// TODO (Christian) Add a remove component.
private:
	ComponentManager()	= default;
	~ComponentManager()	= default;

	static ComponentManager* m_instance;
	
	std::vector<Transform>		m_transforms;
	std::vector<SpriteRenderer>	m_spriteRenderers;
	std::vector<BoxCollider>	m_boxColliders;

	entId	m_componentIndices[(entId)ComponentTypes::Count];

};

} // Namespace jci.