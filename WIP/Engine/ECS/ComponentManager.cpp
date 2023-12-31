/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "ComponentManager.h"

namespace jci {

ComponentManager* ComponentManager::m_instance = nullptr;

void ComponentManager::Init()
{
	ASSERT((entId)ComponentTypes::Count <= MAX_COMPONENTS, "Exceeded max number of components.");

	m_transforms.resize(MAX_ENTITIES);
	m_spriteRenderers.resize(MAX_ENTITIES);
	m_boxColliders.resize(MAX_ENTITIES);
	m_circleColliders.resize(MAX_ENTITIES);
	m_capsuleColliders.resize(MAX_ENTITIES);
	m_navBlocks.resize(MAX_ENTITIES);
	m_ais.resize(MAX_ENTITIES);
	m_impulses.resize(MAX_ENTITIES);
	m_audios.resize(MAX_ENTITIES);
	m_animations.resize(MAX_ENTITIES);
	m_particleEmissions.resize(MAX_ENTITIES);
	m_uiButtons.resize(MAX_ENTITIES);
	m_uiSprites.resize(MAX_ENTITIES);
	m_uiTexts.resize(MAX_ENTITIES);

	ResetComponents();
}

void ComponentManager::Destroy()
{
	m_transforms.clear();
	m_spriteRenderers.clear();
	m_boxColliders.clear();
	m_circleColliders.clear();
	m_capsuleColliders.clear();
	m_navBlocks.clear();
	m_ais.clear();
	m_impulses.clear();
	m_audios.clear();
	m_animations.clear();
	m_particleEmissions.clear();
	m_uiButtons.clear();
	m_uiSprites.clear();
	m_uiTexts.clear();

	delete m_instance;
}

} // Namespace jci.