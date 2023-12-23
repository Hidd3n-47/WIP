#include "pch.h"
#include "PlayerStates.h"

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
		m_idleTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/PlayerIdle.png", 2, 1);
	}

	jci::Animation* anim = m_player->playerEntity->GetComponent<jci::Animation>();
	anim->SetTexture(m_idleTexture);
	anim->SetTimeBetweenFrames(0.8f);
	anim->SetAnimationCount(2);
}

void PlayerIdleState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();

	if (direction != vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Shooting);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_r))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Reloading);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right))
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
		m_movingTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	}

	jci::Animation* anim = m_player->playerEntity->GetComponent<jci::Animation>();
	anim->SetTexture(m_movingTexture);
	anim->SetAnimationCount(1);
}

void PlayerMovingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();

	if (direction == vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Shooting);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_r))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Reloading);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Right))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Melee);
		return;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_Space))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Dashing);
		return;
	}

	*(m_player->position) += direction * m_player->speed * dt;
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

	jci::Animation* anim = m_player->playerEntity->GetComponent<jci::Animation>();
	anim->SetTexture(m_movingTexture);
	anim->SetAnimationCount(1);
}

void PlayerDashingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();

	*(m_player->position) += direction * m_player->speed * 5.0f * dt;

	if (direction == vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
	}
	else
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
	}

	
}

void PlayerDashingState::OnStateExit()
{
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
	m_player->m_knife->GetComponent<jci::Transform>()->SetPosition(*m_player->position + (m_player->GetInputDirection() * 0.7f));
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
		}
		else
		{
			PlayerStateManager::Instance()->SetState(PlayerState::Moving);
		}
	}
}

void PlayerMeleeState::OnStateExit()
{
	delete m_player->stabbin;
	m_player->m_knife->AddComponent<jci::SpriteRenderer>()->SetTexture(m_player->m_blankTexture);
	m_player->m_knife->GetComponent<jci::Transform>()->SetPosition(vec2(200.0f, 200.0f));
}

// ----------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Shooting State --------------------------------------------------------------

void PlayerShootingState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
	}

	m_player->m_equippedGun->FireGun(m_player->time, *m_player->position, jci::SceneManager::Instance()->GetCurrentScene(), vec2(m_player->m_width * 0.5f, m_player->m_height * 0.5f));
}

void PlayerShootingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();
	if (direction != vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
	}
	else
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
	}
}

void PlayerShootingState::OnStateExit()
{

}

// ---------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------- Player Reloading State --------------------------------------------------------------

void PlayerReloadingState::OnStateEnter()
{
	if (!m_player)
	{
		m_player = PlayerStateManager::Instance()->GetPlayer();
	}

	m_player->m_equippedGun->m_inClip = m_player->m_equippedGun->m_magSize;
}

void PlayerReloadingState::OnStateUpdate(float dt)
{
	vec2 direction = m_player->GetInputDirection();
	if (direction != vec2(0.0f))
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Moving);
	}
	else
	{
		PlayerStateManager::Instance()->SetState(PlayerState::Idle);
	}
}

void PlayerReloadingState::OnStateExit()
{

}

// ---------------------------------------------------------------------------------------------------------------------------------------