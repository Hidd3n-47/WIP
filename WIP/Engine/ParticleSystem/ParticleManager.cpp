/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "ParticleManager.h"

#include "Random/Random.h"

namespace jci {

ParticleManager* ParticleManager::m_instance = nullptr;

void ParticleManager::Update(float dt)
{
	for (Particle& p : m_particles)
	{
		if (!p.active)
		{
			continue;
		}

		if (p.lifeRemaining <= 0.0f)
		{
			p.active = false;
			continue;
		}

		float movementPercentage = p.movementLifeRemaining / p.movementLifeTime;
		if (movementPercentage >= 0.0f)
		{
			p.movementLifeRemaining -= dt;
			p.position += p.velocity * dt;
			p.rotation += 0.001f * dt;
		}
		
		p.lifeRemaining -= dt;

		float percentage = p.lifeRemaining / p.lifeTime;
		p.color.a = percentage;
		p.size = p.endSize + percentage * (p.startSize - p.endSize);
	}
}

void ParticleManager::Emit(const ParticleProperties& properties)
{
	for (int i = 0; i < properties.numParticles; i++)
	{
		Particle& particle = m_particles[m_particleIndex];
		particle.active = true;
		particle.position = properties.position;
		particle.rotation = Random::Instance()->Rand() * 360.0f;

		particle.velocity = properties.direction * properties.speed;
		particle.velocity.x += properties.velocityVariation.x * (Random::Instance()->Rand() - 0.5f);
		particle.velocity.y += properties.velocityVariation.y * (Random::Instance()->Rand() - 0.5f);

		particle.color = properties.color;

		particle.lifeTime = properties.lifeTime;
		particle.lifeRemaining = particle.lifeTime;
		particle.movementLifeTime = properties.movementLifeTime;
		particle.movementLifeRemaining = particle.movementLifeTime;
		particle.startSize = properties.startSize + properties.sizeVariation * (Random::Instance()->Rand() - 0.5f);
		particle.endSize = properties.endSize;

		m_particleIndex = (m_particleIndex + 1) % MAX_PARTICLES;
	}
}

} // Namespace jci.