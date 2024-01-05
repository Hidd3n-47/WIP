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
	void Destroy();

	template<class ComponentClass>
	inline ComponentClass* RegisterComponent(ComponentTypes type, std::vector<ComponentClass>& componentVector)
	{
		entId componentIndex = m_componentIndices[(entId)type]++;

		ComponentClass comp;
		comp.SetId(componentIndex);
		componentVector[componentIndex] = comp;
		return &componentVector[componentIndex];
	}

	template<class ComponentClass>
	inline ComponentClass* RegisterComponent(ComponentTypes type, std::vector<ComponentClass>& componentVector, ComponentClass component)
	{
		entId componentIndex = m_componentIndices[(entId)type]++;

		component.SetId(componentIndex);
		componentVector[componentIndex] = component;
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
			componentVector[componentSize].OnComponentRemove();
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

	inline IComponent* GetComponentCopy(ComponentTypes type, entId id)
	{
		switch (type)
		{
		case ComponentTypes::Transform:
		{
			//Transform t = m_transforms[id];
			Transform* t = new Transform(m_transforms[id]);
			return dynamic_cast<IComponent*>(t);
		}
		case ComponentTypes::SpriteRenderer:
		{
			//SpriteRenderer sr = m_spriteRenderers[id];
			SpriteRenderer* sr = new SpriteRenderer(m_spriteRenderers[id]);
			return dynamic_cast<IComponent*>(sr);
		}
		case ComponentTypes::BoxCollider:
		{
			//BoxCollider bc = m_boxColliders[id];
			BoxCollider* bc = new BoxCollider(m_boxColliders[id]);
			return dynamic_cast<IComponent*>(bc);
		}
		case ComponentTypes::CircleCollider:
		{
			//CircleCollider cc = m_circleColliders[id];
			CircleCollider* cc = new CircleCollider(m_circleColliders[id]);
			return dynamic_cast<IComponent*>(cc);
		}
		case ComponentTypes::CapsuleCollider:
		{
			//CapsuleCollider cc = m_capsuleColliders[id];
			CapsuleCollider* cc = new CapsuleCollider(m_capsuleColliders[id]);
			return dynamic_cast<IComponent*>(cc);
		}
		case ComponentTypes::NavBlock:
		{
			//NavBlock nb = m_navBlocks[id];
			NavBlock* nb = new NavBlock(m_navBlocks[id]);
			return dynamic_cast<IComponent*>(nb);
		}
		case ComponentTypes::AI:
		{
			//AI ai = m_ais[id];
			AI* ai = new AI(m_ais[id]);
			return dynamic_cast<IComponent*>(ai);
		}
		case ComponentTypes::Impulse:
		{
			//Impulse i = m_impulses[id];
			Impulse* i = new Impulse(m_impulses[id]);
			return dynamic_cast<IComponent*>(i);
		}
		case ComponentTypes::Audio:
		{
			//Audio a = m_audios[id];
			Audio* a = new Audio(m_audios[id]);
			return dynamic_cast<IComponent*>(a);
		}
		case ComponentTypes::Animation:
		{
			//Animation a = m_animations[id];
			Animation* a = new Animation(m_animations[id]);
			return dynamic_cast<IComponent*>(a);
		}
		case ComponentTypes::ParticleEmission:
		{
			//ParticleEmission pe = m_particleEmissions[id];
			ParticleEmission* pe = new ParticleEmission(m_particleEmissions[id]);
			return dynamic_cast<IComponent*>(pe);
		}
		case ComponentTypes::UiButton:
		{
			//UiButton ub = m_uiButtons[id];
			UiButton* ub = new UiButton(m_uiButtons[id]);
			return dynamic_cast<IComponent*>(ub);
		}
		case ComponentTypes::UiSprite:
		{
			//UiSprite us = m_uiSprites[id];
			UiSprite*us = new UiSprite(m_uiSprites[id]);
			return dynamic_cast<IComponent*>(us);
		}
		default:
			ASSERT(false, "Unhandled component removal.");
			return nullptr;
		}
	}

	void RegisterCachedComponent(IComponent* component)
	{
		const ComponentTypes type = component->GetComponentType();
		switch (type)
		{
		case ComponentTypes::Transform:
			RegisterComponent(type, m_transforms, *dynamic_cast<Transform*>(component));
			break;
		case ComponentTypes::SpriteRenderer:
			RegisterComponent(type, m_spriteRenderers, *dynamic_cast<SpriteRenderer*>(component));
			break;
		case ComponentTypes::BoxCollider:
			RegisterComponent(type, m_boxColliders, *dynamic_cast<BoxCollider*>(component));
			break;
		case ComponentTypes::CircleCollider:
			RegisterComponent(type, m_circleColliders, *dynamic_cast<CircleCollider*>(component));
			break;
		case ComponentTypes::CapsuleCollider:
			RegisterComponent(type, m_capsuleColliders, *dynamic_cast<CapsuleCollider*>(component));
			break;
		case ComponentTypes::NavBlock:
			RegisterComponent(type, m_navBlocks, *dynamic_cast<NavBlock*>(component));
			break;
		case ComponentTypes::AI:
			RegisterComponent(type, m_ais, *dynamic_cast<AI*>(component));
			break;
		case ComponentTypes::Impulse:
			RegisterComponent(type, m_impulses, *dynamic_cast<Impulse*>(component));
			break;
		case ComponentTypes::Audio:
			RegisterComponent(type, m_audios, *dynamic_cast<Audio*>(component));
			break;
		case ComponentTypes::Animation:
			RegisterComponent(type, m_animations, *dynamic_cast<Animation*>(component));
			break;
		case ComponentTypes::ParticleEmission:
			RegisterComponent(type, m_particleEmissions, *dynamic_cast<ParticleEmission*>(component));
			break;
		case ComponentTypes::UiButton:
			RegisterComponent(type, m_uiButtons, *dynamic_cast<UiButton*>(component));
			break;
		case ComponentTypes::UiSprite:
			RegisterComponent(type, m_uiSprites, *dynamic_cast<UiSprite*>(component));
			break;
		default:
			ASSERT(false, "Unhandled component removal.");
			break;
		}
	}
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