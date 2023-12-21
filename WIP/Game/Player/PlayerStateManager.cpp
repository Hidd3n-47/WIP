#include "pch.h"
#include "PlayerStateManager.h"

#include <Engine/Graphics/Texture/TextureManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Scene/SceneManager.h>

#include "PlayerStates.h"

vec2 PlayerS::GetInputDirection()
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

PlayerStateManager* PlayerStateManager::m_instance = nullptr;

PlayerStateManager::PlayerStateManager()
{
	m_playerStates.push_back(new PlayerIdleState());
	m_playerStates.push_back(new PlayerMovingState());

}

PlayerStateManager::~PlayerStateManager()
{
	for (size_t i = 0; i < m_playerStates.size(); i++)
	{
		delete m_playerStates[i];
	}
}

void PlayerStateManager::Init(vec2 playerStartPosition)
{
	// Set up the player.
	m_player = PlayerS();
	jci::Scene* currentScene = jci::SceneManager::Instance()->GetCurrentScene();

	m_player.playerEntity = currentScene->CreateEmptyEntity();
	m_player.playerEntity->SetTag("Player");

	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Scientist.png");
	m_player.playerEntity->AddComponent<jci::Animation>()->SetTexture(text);

	jci::CapsuleCollider* cc = m_player.playerEntity->AddComponent<jci::CapsuleCollider>();
	cc->SetBodyType(jci::BodyType::Kinematic);
	cc->SetCollisionMethods(this);

	m_player.position = m_player.playerEntity->GetComponent<jci::Transform>()->GetPositionPointer();
	*m_player.position = playerStartPosition;

	currentScene->GetCamera()->SetFollowPosition(m_player.position);

	m_playerStates[(int)m_state]->OnStateEnter();
}

void PlayerStateManager::Update(float dt)
{
	m_playerStates[(int)m_state]->OnStateUpdate(dt);
}

void PlayerStateManager::SetState(PlayerState state)
{
	m_playerStates[(int)m_state]->OnStateExit(); 
	m_state = state; 
	m_playerStates[(int)m_state]->OnStateEnter();
}

void PlayerStateManager::OnCollisionEnter(jci::Entity* other)
{
}

void PlayerStateManager::OnCollisionStay(jci::Entity* other)
{
}

void PlayerStateManager::OnCollisionExit(jci::Entity* other)
{
}