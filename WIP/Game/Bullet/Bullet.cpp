#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(jci::Entity* e, vec2 d)
{
	body = e;
	direction = d;
	spawnTime = SDL_GetTicks();
	isMove = true;
}

void Bullet::Update()
{
	
}

bool Bullet::GetMove()
{
	return isMove;
}

void Bullet::SetMove(bool moves)
{
	isMove = moves;
}

int Bullet::GetSpawnTime()
{
	return spawnTime;
}

void Bullet::Destroy()
{
	delete body;
}