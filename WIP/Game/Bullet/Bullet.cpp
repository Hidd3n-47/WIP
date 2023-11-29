#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(jci::Entity* e, vec2 d)
{
	body = e;
	direction = d;
}