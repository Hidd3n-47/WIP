#pragma once

class BulletImpact;

namespace jci {
class Timer;
}

class BulletImpactManager
{
public:
	inline static BulletImpactManager* Instance() { return !m_instance ? m_instance = new BulletImpactManager() : m_instance; }

	void Init();
	void Destory();

	void Update();

	void SpawnBulletImpact(vec2 position);

	static const uint32 NUM_BULLET_IMPACT_PREFABS = 5;
private:
	BulletImpactManager() = default;
	~BulletImpactManager() = default;

	static BulletImpactManager* m_instance;

	uint32 m_impactPrefabIndex = 0;
	uint32 m_bulletImpactTexture = 0;

	std::array<BulletImpact*, NUM_BULLET_IMPACT_PREFABS> m_bulletImpact = { 0 };
	std::array<jci::Timer*, NUM_BULLET_IMPACT_PREFABS> m_bulletImpactTimers = { 0 };
};

