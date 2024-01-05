#include "pch.h"
#include "Player.h"

#include <Engine/Time/Timer.h>
#include <Engine/ECS/Entity.h>
#include <Engine/Input/InputManager.h>

Player::~Player()
{
	delete stabbin;
	delete dashCD;
	delete bulletCD;
	delete meleeCD;
	delete reload;
}

vec2 Player::GetInputDirection()
{
	vec2 direction = vec2(0.0f);

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_w))
	{
		direction += vec2(0.0f, 1.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_s))
	{
		direction += vec2(0.0f, -1.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_a))
	{
		direction += vec2(-1.0f, 0.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_d))
	{
		direction += vec2(1.0f, 0.0f);
	}

	return direction;
}

void Player::DamagePlayer(int damage)
{
	if (!m_iFrameActive)
	{
		m_hp -= damage;
		std::cout << m_hp << std::endl;
		UpdateHealthUi();
	}
}


void Player::MaxHpUp()
{
	m_hp += 10;
	m_maxHp += 10;
}

void Player::FasterReload()
{
	if (m_equippedGun->m_reloadTimer > 0.5f)
	{
		m_equippedGun->m_reloadTimer -= 0.1f;
	}
}

void Player::FasterFireRate()
{
	if (m_equippedGun->GetFireRate() > 0.25f)
	{
		m_equippedGun->SetFireRate(m_equippedGun->GetFireRate() - 0.15f);
	}
}

void Player::DmgUpRateDown()
{
	m_equippedGun->SetBulletDamage(m_equippedGun->GetBulletDamage() + 3.0f);
	m_equippedGun->SetFireRate(m_equippedGun->GetFireRate() + 0.15f);
}

void Player::RateUpDmgDown()
{
	if (m_equippedGun->GetFireRate() > 0.4f && m_equippedGun->GetBulletDamage() > 5)
	{
		m_equippedGun->SetBulletDamage(m_equippedGun->GetBulletDamage() - 1.0f);
		m_equippedGun->SetFireRate(m_equippedGun->GetFireRate() - 0.3f);
	}
	else if (m_equippedGun->GetFireRate() > 0.25f && m_equippedGun->GetBulletDamage() > 5)
	{
		m_equippedGun->SetBulletDamage(m_equippedGun->GetBulletDamage() - 1.0f);
		m_equippedGun->SetFireRate(0.25f);
	}
}

void Player::LessDashCD()
{
	if (m_dashTime > 0.5f)
	{
		m_dashTime -= 0.3f;
	}
}