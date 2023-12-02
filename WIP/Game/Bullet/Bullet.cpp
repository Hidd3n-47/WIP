#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(jci::Entity* e, vec2 d)
{
	body = e;
	direction = d;
	spawnTime = SDL_GetTicks();
}

void Bullet::Update()
{
	
}

int Bullet::GetSpawnTime()
{
	return spawnTime;
}

void Bullet::Destroy()
{
	delete body;
}