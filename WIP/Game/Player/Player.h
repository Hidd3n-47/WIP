#pragma once

#include "Game/Gun/Gun.h"
#include <Game/Bullet/BulletManager.h>

namespace jci
{
class Entity;
class Timer;
}

class Player
{
	friend class PlayerStateManager;
	friend class PlayerIdleState;
	friend class PlayerMovingState;
	friend class PlayerDashingState;
	friend class PlayerMeleeState;
	friend class PlayerReloadingState;
	friend class PlayerShootingState;
public:
	Player() = default;
	~Player();

	void SetManager(BulletManager* mgr);
	void MaxHpUp();
	void FasterReload();
	void FasterFireRate();
	void DmgUpRateDown();
	void RateUpDmgDown();
	void LessDashCD();
	void Pierce();
	void DamagePlayer(int damage);
	vec2 GetInputDirection();

	inline void UpdateAmmoUi() const { m_equippedGun->UpdateAmmoUi(); }
	inline void UpdateHealthUi() const { m_healthUiEnt->GetComponent<jci::UiSprite>()->SetTextureRenderPercentage(m_hp / (float)m_maxHp); }

	inline vec2 GetPosition() const { return *m_position; }
private:
	jci::Entity* m_playerEntity	= nullptr;
	jci::Entity* m_healthUiEnt	= nullptr;
	jci::Entity* m_healthBarEnt	= nullptr;
	jci::Entity* m_knife		= nullptr;

	vec2* m_position = nullptr;

	jci::Timer* m_stabbin			= nullptr;
	jci::Timer* m_dashCD			= nullptr;
	jci::Timer* m_bulletCD		= nullptr;
	jci::Timer* m_meleeCD			= nullptr;
	jci::Timer* m_reload			= nullptr;
	jci::Timer* m_iFrameTimer	= nullptr;

	Gun* m_equippedGun = nullptr;

	BulletManager* manager = nullptr;

	uint32			m_blankTexture = 0;
	uint32			m_knifeTexture = 0;
	float			m_speed = 5.0f;
	float			m_time = 0.0f;
	bool			m_canFire = true;
	bool			m_canStab = true;
	bool			m_canDash = true;
	bool			m_hasReloaded = false;
	bool			m_tripSwitch = false;
	float			m_dashTime = 0.0f;
	float			m_stabTime = 0.0f;
	int				m_maxHp = 100;
	int				m_hp = m_maxHp;
	bool			m_iFrameActive = false;
};

