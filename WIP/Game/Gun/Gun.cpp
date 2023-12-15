#include "pch.h"
#include "Gun.h"

Gun::Gun()
{

}

void Gun::Create(int rateOfFire)
{
	m_fireRate = rateOfFire;
}

int Gun::GetFireRate()
{
	return m_fireRate;
}