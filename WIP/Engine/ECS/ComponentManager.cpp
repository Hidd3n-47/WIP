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

	ResetComponents();
}

} // Namespace jci.