#pragma once

#include "Game/Gun/Gun.h"

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

	void MaxHpUp();
	void FasterReload();
	void FasterFireRate();
	void DmgUpRateDown();
	void RateUpDmgDown();
	void LessDashCD();
	void DamagePlayer(int damage);
	vec2 GetInputDirection();

	inline void UpdateHealthUi() const { m_healthUiEnt->GetComponent<jci::UiSprite>()->SetTextureRenderPercentage(m_hp / (float)m_maxHp); }

	inline vec2 GetPosition() const { return *m_position; }
private:
	jci::Entity* playerEntity	= nullptr;
	jci::Entity* m_healthUiEnt	= nullptr;
	jci::Entity* m_knife		= nullptr;

	vec2* m_position = nullptr;

	jci::Timer* stabbin			= nullptr;
	jci::Timer* dashCD			= nullptr;
	jci::Timer* bulletCD		= nullptr;
	jci::Timer* meleeCD			= nullptr;
	jci::Timer* reload			= nullptr;
	jci::Timer* m_iFrameTimer	= nullptr;

	Gun* m_equippedGun = nullptr;

	uint32			m_blankTexture;
	uint32			m_knifeTexture;
	float			speed = 5.0f;
	float			m_width;
	float			m_height;
	float			time;
	bool			m_canFire = true;
	bool			m_canStab = true;
	bool			m_canDash = true;
	bool			hasReloaded = false;
	bool			tripSwitch = false;
	float			m_dashTime;
	float			m_stabTime;
	int				m_maxHp = 50;
	int				m_hp = m_maxHp;
	bool			m_iFrameActive = false;
};

