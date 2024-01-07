#include "pch.h"
#include "BulletImpactManager.h"

#include <Engine/Time/Timer.h>
#include <Engine/Graphics/Texture/TextureManager.h>

#include "BulletImpact.h"

BulletImpactManager* BulletImpactManager::m_instance = nullptr;

void BulletImpactManager::Init()
{
	m_bulletImpactTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/ImpactEffect.png", 3, 1);

	for (uint32 i = 0; i < NUM_BULLET_IMPACT_PREFABS; i++)
	{
		m_bulletImpact[i] = new BulletImpact(m_bulletImpactTexture);
	}
}

void BulletImpactManager::Destory()
{
	for (uint32 i = 0; i < NUM_BULLET_IMPACT_PREFABS; i++)
	{
		delete m_bulletImpact[i];
		m_bulletImpact[i] = nullptr;

		delete m_bulletImpactTimers[i];
		m_bulletImpactTimers[i] = nullptr;
	}

	delete m_instance;
}

void BulletImpactManager::Update()
{
	for (uint32 i = 0; i < NUM_BULLET_IMPACT_PREFABS; i++)
	{
		if (m_bulletImpactTimers[i] && m_bulletImpactTimers[i]->TimerTick() == jci::TimerStatus::TimerCompleted)
		{
			delete m_bulletImpactTimers[i];
			m_bulletImpactTimers[i] = nullptr;
			m_bulletImpact[i]->Deactivate();
		}
	}
}

void BulletImpactManager::SpawnBulletImpact(vec2 position)
{
	m_bulletImpact[m_impactPrefabIndex]->SetActive(position);
	m_bulletImpactTimers[m_impactPrefabIndex] = new jci::Timer(0.15f);
}