#include "pch.h"
#include "Bullet.h"

#include <Engine/ECS/ParticleEmission.h>

#include "BulletImpactManager.h"

Bullet::Bullet(jci::Entity* e)
{
	m_body = e;
	m_direction = vec2(0,0);
	m_spawnTime = 0;
	m_isMove = false;
	m_dmg = 10;
	m_pierced = 1;

	e->GetComponent<jci::BoxCollider>()->SetCollisionMethods(this);
	jci::ParticleEmission* particles = e->AddComponent<jci::ParticleEmission>();

	jci::ParticleProperties props;
	props.position = vec2(6, -6);
	props.color = vec4(0.533f, 0.031f, 0.031f, 1.0f);
	props.sizeVariation = 0.05f;
	props.lifeTime = 4.6f;
	props.movementLifeTime = 0.15f;
	props.startSize = 0.1f;
	props.endSize = 0.05f;
	props.speed = 8.0f;
	props.velocityVariation = vec2(3.5f, 3.8f);
	props.numParticles = 20;
	particles->SetProperties(props);
}

void Bullet::BulletFire(vec2 d)
{
	m_direction = d;
	m_spawnTime = SDL_GetTicks();
	m_isMove = true;
}

void Bullet::SetActive(vec2 playerPosition, vec2 dir, float angle)
{
	m_body->SetActive(true);
	m_isMove = true;

	jci::Transform* t = m_body->GetComponent<jci::Transform>();
	t->SetPosition(playerPosition);
	t->SetRotation(angle);
	
	jci::Animation* a = m_body->GetComponent<jci::Animation>();
	a->SetAnimationCount(4);

	m_direction = dir;
}

void Bullet::Update()
{
	
}

bool Bullet::GetMove()
{
	return m_isMove;
}

int Bullet::GetDmg()
{
	return m_dmg;
}

void Bullet::PierceUp(int pierceNum)
{
	m_pierced = pierceNum;
}

void Bullet::SetDmg(int damage)
{
	m_dmg = damage;
}

void Bullet::Delete()
{
	m_isMove = false;
}

int Bullet::GetSpawnTime()
{
	return m_spawnTime;
}

void Bullet::Destroy()
{
	delete m_body;
}

void Bullet::OnCollisionEnter(jci::Entity* other)
{
	jci::Transform* trans = m_body->GetComponent<jci::Transform>();

	if (other->GetTag() == "Enemy")
	{
		DLOG("Pierce: " + std::to_string(m_pierced));
		jci::ParticleEmission* particles = m_body->GetComponent<jci::ParticleEmission>();
		particles->SetParticlePosition(m_body->GetComponent<jci::Transform>()->GetPosition());
		particles->SetParticleDirection(glm::normalize(m_direction));
		particles->Emit();
		m_pierced -= 1;
	}
	if (!(other->GetTag() == "Player" || other->GetTag() == "Bullet") && m_pierced < 1 || other->GetTag() == "Wall")
	{
		BulletImpactManager::Instance()->SpawnBulletImpact(trans->GetPosition());
		trans->SetPosition(vec2(10000000.0f));
	}

}

void Bullet::OnCollisionStay(jci::Entity* other)
{
}

void Bullet::OnCollisionExit(jci::Entity* other)
{
}