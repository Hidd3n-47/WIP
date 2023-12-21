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
		//*(m_player->position) += direction * m_player->speed * dt;
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		// Shoot.
		DLOG("Shooting.");
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
	}

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		// Shoot.
		DLOG("Shooting.");
	}

	*(m_player->position) += direction * m_player->speed * dt;
}

void PlayerMovingState::OnStateExit()
{
}

// ---------------------------------------------------------------------------------------------------------------------------------------