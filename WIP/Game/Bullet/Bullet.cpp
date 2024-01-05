#include "pch.h"
#include "Bullet.h"

#include <Engine/ECS/ParticleEmission.h>

Bullet::Bullet(jci::Entity* e)
{
	body = e;
	direction = vec2(0,0);
	spawnTime = 0;
	isMove = false;
	dmg = 10;
	m_pierced = 1;

	e->GetComponent<jci::BoxCollider>()->SetCollisionMethods(this);
	m_particles = e->AddComponent<jci::ParticleEmission>();

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
	m_particles->SetProperties(props);
}

void Bullet::bulletFire(vec2 d)
{
	direction = d;
	spawnTime = SDL_GetTicks();
	isMove = true;
}

void Bullet::SetActive(vec2 playerPosition, vec2 dir, float angle)
{
	body->SetActive(true);
	isMove = true;

	jci::Transform* t = body->GetComponent<jci::Transform>();
	t->SetPosition(playerPosition);
	t->SetRotation(angle);
	
	jci::Animation* a = body->GetComponent<jci::Animation>();
	a->SetAnimationCount(4);

	direction = dir;
}

void Bullet::Update()
{
	
}

bool Bullet::GetMove()
{
	return isMove;
}

int Bullet::GetDmg()
{
	return dmg;
}

void Bullet::PierceUp(int pierceNum)
{
	m_pierced = pierceNum;
}

void Bullet::SetDmg(int damage)
{
	dmg = damage;
}

void Bullet::Delete()
{
	isMove = false;
}

int Bullet::GetSpawnTime()
{
	return spawnTime;
}

void Bullet::Destroy()
{
	delete body;
}

void Bullet::OnCollisionEnter(jci::Entity* other)
{
	if (other->GetTag() == "Enemy")
	{
		DLOG("Pierce: " + std::to_string(m_pierced));
		m_particles->SetParticlePosition(body->GetComponent<jci::Transform>()->GetPosition());
		m_particles->SetParticleDirection(glm::normalize(direction));
		m_particles->Emit();
		m_pierced -= 1;
	}
	if (!(other->GetTag() == "Player" || other->GetTag() == "Bullet") && m_pierced < 1)
	{
		body->GetComponent<jci::Transform>()->SetPosition(vec2(10000000.0f));
	}
}

void Bullet::OnCollisionStay(jci::Entity* other)
{
}

void Bullet::OnCollisionExit(jci::Entity* other)
{
}