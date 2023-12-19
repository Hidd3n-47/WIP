#pragma once

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "NavBlock.h"
#include "AI.h"
#include "Impulse.h"
#include "Audio.h"
#include "Animation.h"
#include "ParticleEmission.h"

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
	inline T* AddComponent(IProperties* properties)
	{
		ASSERT(false, "Unhandled component added.");
		return nullptr;
	}

	template<>
	inline Transform* AddComponent<Transform>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::Transform, m_transforms);
	}

	template<>
	inline SpriteRenderer* AddComponent<SpriteRenderer>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::SpriteRenderer, m_spriteRenderers);
	}

	template<>
	inline BoxCollider* AddComponent<BoxCollider>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::BoxCollider, m_boxColliders);
	}

	template<>
	inline CircleCollider* AddComponent<CircleCollider>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::CircleCollider, m_circleColliders);
	}

	template<>
	inline NavBlock* AddComponent<NavBlock>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::NavBlock, m_navBlocks);
	}

	template<>
	inline AI* AddComponent<AI>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::AI, m_ais);
	}

	template<>
	inline Impulse* AddComponent<Impulse>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::Impulse, m_impulses);
	}

	template<>
	inline Audio* AddComponent<Audio>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::Audio, m_audios);
	}

	template<>
	inline Animation* AddComponent<Animation>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::Animation, m_animations);
	}

	template<>
	inline ParticleEmission* AddComponent<ParticleEmission>(IProperties* properties)
	{
		return RegisterComponent(ComponentTypes::ParticleEmission, m_particleEmissions);
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
	inline CircleCollider* GetComponent<CircleCollider>(entId componentId)
	{
		return RetrieveComponent(m_circleColliders, componentId);
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

	template<>
	inline Impulse* GetComponent<Impulse>(entId componentId)
	{
		return RetrieveComponent(m_impulses, componentId);
	}

	template<>
	inline Audio* GetComponent<Audio>(entId componentId)
	{
		return RetrieveComponent(m_audios, componentId);
	}

	template<>
	inline Animation* GetComponent<Animation>(entId componentId)
	{
		return RetrieveComponent(m_animations, componentId);
	}

	template<>
	inline ParticleEmission* GetComponent<ParticleEmission>(entId componentId)
	{
		return RetrieveComponent(m_particleEmissions, componentId);
	}

	template<class ComponentClass>
	inline Entity* DeregisterComponent(ComponentTypes type, std::vector<ComponentClass>& componentVector, entId id)
	{
		ASSERT(componentVector[id].GetId() != invalid_id, "Component has invalid id whilst existing.");

		m_componentIndices[(entId)type]--;
		componentVector[id].OnComponentRemove();
		componentVector[id] = componentVector.back();
		componentVector.back().SetId(invalid_id);
		return componentVector.back().GetEntity();
	}

	inline Entity* RemoveComponent(ComponentTypes type, entId id)
	{
		switch (type)
		{
		case ComponentTypes::Transform:
			return DeregisterComponent(type, m_transforms, id);
		case ComponentTypes::SpriteRenderer:
			return DeregisterComponent(type, m_spriteRenderers, id);
		case ComponentTypes::BoxCollider:
			return DeregisterComponent(type, m_boxColliders, id);
		case ComponentTypes::CircleCollider:
			return DeregisterComponent(type, m_circleColliders, id);
		case ComponentTypes::NavBlock:
			return DeregisterComponent(type, m_navBlocks, id);
		case ComponentTypes::AI:
			return DeregisterComponent(type, m_ais, id);
		case ComponentTypes::Impulse:
			return DeregisterComponent(type, m_impulses, id);
		case ComponentTypes::Audio:
			return DeregisterComponent(type, m_audios, id);
		case ComponentTypes::Animation:
			return DeregisterComponent(type, m_animations, id);
		case ComponentTypes::ParticleEmission:
			return DeregisterComponent(type, m_particleEmissions, id);
		default:
			ASSERT(false, "Unhandled component removal.");
			return nullptr;
		}
	}

	/*template<class T>
	inline Entity* RemoveComponent(entId id)
	{
		ASSERT(false, "Unhandled component removal.");
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::Transform>(entId id)
	{
		return DeregisterComponent(m_transforms, id);
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::SpriteRenderer>(entId id)
	{
		return DeregisterComponent(ComponentTypes::SpriteRenderer, m_spriteRenderers, id);
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::BoxCollider>(entId id)
	{
		return DeregisterComponent(ComponentTypes::BoxCollider, m_boxColliders, id);
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::NavBlock>(entId id)
	{
		return DeregisterComponent(ComponentTypes::NavBlock, m_navBlocks, id);
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::AI>(entId id)
	{
		return DeregisterComponent(ComponentTypes::AI, m_ais, id);
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::Impulse>(entId id)
	{
		return DeregisterComponent(ComponentTypes::Impulse, m_impulses, id);
	}

	template<>
	inline Entity* RemoveComponent<ComponentTypes::Audio>(entId id)
	{
		return DeregisterComponent(ComponentTypes::Audio, m_audios, id);
	}
	
	template<>
	inline Entity * RemoveComponent<ComponentTypes::Animation>(entId id)
	{
		return DeregisterComponent(ComponentTypes::Animation, m_animations, id);
	}*/

	template<class T>
	inline T* GetComponentVector()
	{
		ASSERT(false, "Getting the Component Vector has not been implemented.");

		return;
	}

	template<>
	inline Transform* GetComponentVector()
	{ 
		return &m_transforms[0];
	}

	template<>
	inline SpriteRenderer* GetComponentVector()
	{ 
		return &m_spriteRenderers[0];
	}

	template<>
	inline BoxCollider* GetComponentVector()
	{ 
		return &m_boxColliders[0];
	}

	template<>
	inline CircleCollider* GetComponentVector()
	{
		return &m_circleColliders[0];
	}

	template<>
	inline NavBlock* GetComponentVector()
	{ 
		return &m_navBlocks[0];
	}

	template<>
	inline AI* GetComponentVector()
	{
		return &m_ais[0];
	}

	template<>
	inline Impulse* GetComponentVector()
	{
		return &m_impulses[0];
	}

	template<>
	inline Audio* GetComponentVector()
	{
		return &m_audios[0];
	}

	template<>
	inline Animation* GetComponentVector()
	{
		return &m_animations[0];
	}

	template<>
	inline ParticleEmission* GetComponentVector()
	{
		return &m_particleEmissions[0];
	}

	inline entId GetComponentCount(ComponentTypes type) const { return m_componentIndices[(entId)type]; }

	// TODO (Christian) Add a remove component.
private:
	ComponentManager()	= default;
	~ComponentManager()	= default;

	static ComponentManager* m_instance;
	
	std::vector<Transform>			m_transforms;
	std::vector<SpriteRenderer>		m_spriteRenderers;
	std::vector<BoxCollider>		m_boxColliders;
	std::vector<CircleCollider>		m_circleColliders;
	std::vector<NavBlock>			m_navBlocks;
	std::vector<AI>					m_ais;
	std::vector<Impulse>			m_impulses;
	std::vector<Audio>				m_audios;
	std::vector<Animation>			m_animations;
	std::vector<ParticleEmission>	m_particleEmissions;

	entId	m_componentIndices[(entId)ComponentTypes::Count];
};

} // Namespace jci.