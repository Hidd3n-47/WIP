#pragma once

namespace jci {

struct ParticleProperties
{
	vec2	position			= vec2(0.0f);
	vec2	direction			= vec2(1.0f, 0.0f);
	float	speed				= 5.0f;
	vec2	velocityVariation	= vec2(1.0f);
	vec4	color				= vec4(1.0f);
	float	startSize			= 1.0f;
	float	endSize				= 1.0f;
	float	sizeVariation		= 0.0f;

	float	lifeTime			= 1.0f;
	float	movementLifeTime	= 1.0f;
	uint32	numParticles		= 1;
};

class ParticleManager
{
	friend class RendererManager;
public:
	inline static ParticleManager* Instance() { return !m_instance ? m_instance = new ParticleManager() : m_instance; }

	inline void Destroy() { m_particles.clear(); delete m_instance; }

	void Update(float dt);

	void Emit(const ParticleProperties& properties);

	const uint16 MAX_PARTICLES = 1500;
private:
	inline ParticleManager() { m_particles.resize(MAX_PARTICLES); }
	~ParticleManager() = default;

	static ParticleManager* m_instance;

	struct Particle
	{
		vec2	position;
		vec2	velocity;
		vec4	color;
		float	startSize;
		float	endSize;
		float	size;
		float	rotation;
		float	lifeTime;
		float	movementLifeTime;
		float	lifeRemaining;
		float	movementLifeRemaining;
		bool	active;
	};
	std::vector<Particle> m_particles;
	uint16 m_particleIndex = 0;
};

}// Namespace jci.