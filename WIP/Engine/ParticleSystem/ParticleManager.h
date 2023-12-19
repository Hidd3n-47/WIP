#pragma once

namespace jci {

struct ParticleProperties
{
	vec2	position;
	vec2	velocity;
	vec2	velocityVariation;
	vec4	color;
	float	startSize;
	float	endSize;
	float	sizeVariation;

	float	lifeTime		= 1.0f;
	uint32	numParticles	= 1;
};

class ParticleManager
{
public:
	inline static ParticleManager* Instance() { return !m_instance ? m_instance = new ParticleManager() : m_instance; }

	void Update(float dt);

	void Emit(const ParticleProperties& properties);
private:
	inline ParticleManager() { m_particles.resize(MAX_PARTICLES); }
	~ParticleManager() = default;

	static ParticleManager* m_instance;

	const uint16 MAX_PARTICLES = 1500;

	struct Particle
	{
		vec2	position;
		vec2	velocity;
		vec4	color;
		float	startSize;
		float	endSize;
		float	rotation;
		float	lifeTime;
		float	lifeRemaining;
		bool	active;
	};
	std::vector<Particle> m_particles;
	uint16 m_particleIndex = MAX_PARTICLES - 1;
};

}// Namespace jci.