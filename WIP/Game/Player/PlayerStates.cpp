#include "pch.h"
#include "PlayerStates.h"

#include <Time/Timer.h>
#include <Engine/ECS/Entity.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Graphics/Texture/TextureManager.h>

#include "PlayerStateManager.h"


// ------------------------------------------------------ Player Idle State --------------------------------------------------------------
void PlayerIdleState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
		m_animator = m_player->playerEntity->GetComponent<jci::Animation>();
	}

	m_animator->SetStartIndex(0);
	m_animator->SetAnimationCount(4);
}

void PlayerIdleState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();

	if (direction != vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left) && m_player->m_canFire)
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Shooting);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_r))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Reloading);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right) && m_player->m_canStab)
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Melee);
		return;
	}
}

void PlayerIdleState::OnStateExit()
{
}

// ---------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Moving State --------------------------------------------------------------

void PlayerMovingState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
		m_animator = m_player->playerEntity->GetComponent<jci::Animation>();
	}

	m_animator->SetStartIndex(4);
	m_animator->SetAnimationCount(6);
}

void PlayerMovingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();

	if (direction == vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left) && m_player->m_canFire)
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Shooting);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_r))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Reloading);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right) && m_player->m_canStab)
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Melee);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_Space) && m_player->m_canDash)
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Dashing);
		return;
	}

	*(m_player->m_position) += direction * m_player->speed * dt;

	if (direction.x < 0.0f)
	{
		m_animator->SetVerticalFlip(true);
	}
	else
	{
		m_animator->SetVerticalFlip(false);
	}
}

void PlayerMovingState::OnStateExit()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Dashing State --------------------------------------------------------------

void PlayerDashingState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
		m_movingTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	}

	m_player->m_canDash = false;
	jci::Animation* anim = m_player->playerEntity->GetComponent<jci::Animation>();
	anim->SetTexture(m_movingTexture);
	anim->SetAnimationCount(1);
	vec2 direction = m_player->GetInputDirection();

	m_player->playerEntity->GetComponent<jci::Impulse>()->ImpulseEntity(direction * vec2(20.0f));
}

void PlayerDashingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();

	if (direction == vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
		return;
	}
	else
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
		return;
	}
}

void PlayerDashingState::OnStateExit()
{
	delete m_player->dashCD;
	m_player->dashCD = new jci::Timer(m_player->m_dashTime, false);
}

// ---------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Melee State ---------------------------------------------------------------

void PlayerMeleeState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
	}

	m_player->m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_player->m_knifeTexture);
	m_player->m_knife->GetComponent<jci::Transform>()->SetPosition(*m_player->m_position + (m_player->GetInputDirection() * 0.7f));
	m_player->stabbin = new jci::Timer(3, false);
}

void PlayerMeleeState::OnStateUpdate(float dt)
{
	if (m_player->stabbin->TimerTick() == jci::TimerStatus::TimerCompleted)
	{
		vec2 direction = m_player->GetInputDirection();

		if (direction == vec2(0.0f))
		{
			PlayerStateManager::Instance()->SetState(PlayerState::Idle);
			return;
		}
		else
		{
			PlayerStateManager::Instance()->SetState(PlayerState::Moving);
			return;
		}
	}
}

void PlayerMeleeState::OnStateExit()
{
	delete m_player->stabbin;
	delete m_player->meleeCD;
	m_player->m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_player->m_blankTexture);
	m_player->m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));
	m_player->meleeCD = new jci::Timer(m_player->m_stabTime, false);
}

// ----------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Shooting State --------------------------------------------------------------

void PlayerShootingState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
	}
	m_player->m_canFire = false;
	if (m_player->tripSwitch)
	{
		m_player->m_equippedGun->FireGun(m_player->time, *m_player->m_position, jci::SceneManager::Instance()->GetCurrentScene());
		m_player->tripSwitch = false;
	}
	else
	{
		m_player->tripSwitch = true;
	}
}

void PlayerShootingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();
	if (direction != vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
		return;
	}
	else
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
		return;
	}
}

void PlayerShootingState::OnStateExit()
{
	delete m_player->bulletCD;
	m_player->bulletCD = new jci::Timer(m_player->m_equippedGun->GetFireRate(), false);
}

// ---------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Reloading State --------------------------------------------------------------

void PlayerReloadingState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
	}
	m_player->hasReloaded = false;
	m_player->reload = new jci::Timer(m_player->m_equippedGun->m_reloadTimer, false);
	//m_player->m_equippedGun->m_inClip = m_player->m_equippedGun->m_magSize;
}

void PlayerReloadingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();
	if (direction != vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
		return;
	}
	else
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
		return;
	}
}

void PlayerReloadingState::OnStateExit()
{

}

// ---------------------------------------------------------------------------------------------------------------------------------------