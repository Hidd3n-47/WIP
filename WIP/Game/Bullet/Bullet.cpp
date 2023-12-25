#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(jci::Entity* e)
{
	body = e;
	direction = vec2(0,0);
	spawnTime = 0;
	isMove = false;
	dmg = 10;
}

void Bullet::bulletFire(vec2 d)
{
	//body->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));
	direction = d;
	spawnTime = SDL_GetTicks();
	isMove = true;
}

void Bullet::SetActive(vec2 playerPosition, vec2 dir)
{
	body->SetActive(true);
	isMove = true;
	body->GetComponent<jci::Transform>()->SetPosition(playerPosition);
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
		DLOG("Hit!");
	}
}

void Bullet::OnCollisionStay(jci::Entity* other)
{
}

void Bullet::OnCollisionExit(jci::Entity* other)
{
}