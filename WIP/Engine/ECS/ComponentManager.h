#pragma once

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CapsuleCollider.h"
#include "NavBlock.h"
#include "AI.h"
#include "Impulse.h"
#include "Audio.h"
#include "Animation.h"
#include "ParticleEmission.h"
#include "UiButton.h"
#include "UiSprite.h"

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
	inline CircleCollider* AddComponent<CircleCollider>()
	{
		return RegisterComponent(ComponentTypes::CircleCollider, m_circleColliders);
	}

	template<>
	inline CapsuleCollider* AddComponent<CapsuleCollider>()
	{
		return RegisterComponent(ComponentTypes::CapsuleCollider, m_capsuleColliders);
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

	template<>
	inline Impulse* AddComponent<Impulse>()
	{
		return RegisterComponent(ComponentTypes::Impulse, m_impulses);
	}

	template<>
	inline Audio* AddComponent<Audio>()
	{
		return RegisterComponent(ComponentTypes::Audio, m_audios);
	}

	template<>
	inline Animation* AddComponent<Animation>()
	{
		return RegisterComponent(ComponentTypes::Animation, m_animations);
	}

	template<>
	inline ParticleEmission* AddComponent<ParticleEmission>()
	{
		return RegisterComponent(ComponentTypes::ParticleEmission, m_particleEmissions);
	}

	template<>
	inline UiButton* AddComponent<UiButton>()
	{
		return RegisterComponent(ComponentTypes::UiButton, m_uiButtons);
	}

	template<>
	inline UiSprite* AddComponent<UiSprite>()
	{
		return RegisterComponent(ComponentTypes::UiSprite, m_uiSprites);
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
	inline CapsuleCollider* GetComponent<CapsuleCollider>(entId componentId)
	{
		return RetrieveComponent(m_capsuleColliders, componentId);
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

	template<>
	inline UiButton* GetComponent<UiButton>(entId componentId)
	{
		return RetrieveComponent(m_uiButtons, componentId);
	}

	template<>
	inline UiSprite* GetComponent<UiSprite>(entId componentId)
	{
		return RetrieveComponent(m_uiSprites, componentId);
	}

	template<class ComponentClass>
	inline Entity* DeregisterComponent(ComponentTypes type, std::vector<ComponentClass>& componentVector, entId id)
	{
		ASSERT(componentVector[id].GetId() != invalid_id, "Component has invalid id whilst existing.");

		entId componentSize = --m_componentIndices[(entId)type];

		if (componentSize == id)
		{
			componentVector[componentSize].SetId(invalid_id);
			return nullptr;
		}

		componentVector[id].OnComponentRemove();
		componentVector[id] = componentVector[componentSize];
		componentVector[componentSize].SetId(invalid_id);
		return componentVector[id].GetEntity();
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
		case ComponentTypes::CapsuleCollider:
			return DeregisterComponent(type, m_capsuleColliders, id);
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
		case ComponentTypes::UiButton:
			return DeregisterComponent(type, m_uiButtons, id);
		case ComponentTypes::UiSprite:
			return DeregisterComponent(type, m_uiSprites, id);
		default:
			ASSERT(false, "Unhandled component removal.");
			return nullptr;
		}
	}

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
	inline CapsuleCollider* GetComponentVector()
	{
		return &m_capsuleColliders[0];
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

	template<>
	inline UiButton* GetComponentVector()
	{
		return &m_uiButtons[0];
	}

	template<>
	inline UiSprite* GetComponentVector()
	{
		return &m_uiSprites[0];
	}

	inline entId GetComponentCount(ComponentTypes type) const { return m_componentIndices[(entId)type]; }

	inline void ResetComponents() { memset(m_componentIndices, 0, (entId)ComponentTypes::Count * sizeof(entId)); }
private:
	ComponentManager()	= default;
	~ComponentManager()	= default;

	static ComponentManager* m_instance;
	
	std::vector<Transform>			m_transforms;
	std::vector<SpriteRenderer>		m_spriteRenderers;
	std::vector<BoxCollider>		m_boxColliders;
	std::vector<CircleCollider>		m_circleColliders;
	std::vector<CapsuleCollider>	m_capsuleColliders;
	std::vector<NavBlock>			m_navBlocks;
	std::vector<AI>					m_ais;
	std::vector<Impulse>			m_impulses;
	std::vector<Audio>				m_audios;
	std::vector<Animation>			m_animations;
	std::vector<ParticleEmission>	m_particleEmissions;
	std::vector<UiButton>			m_uiButtons;
	std::vector<UiSprite>			m_uiSprites;

	entId	m_componentIndices[(entId)ComponentTypes::Count];
};

} // Namespace jci.