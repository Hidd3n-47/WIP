#pragma once

#include <Engine/Collision/ICollision.h>
#include <Engine/FSM/IState.h>
#include <Game/Perks/PerkParent.h>

#include "Player.h"

namespace jci
{
	class Entity;
}

enum class PlayerState
{
	Idle = 0,
	Moving,
	Dashing,
	Melee,
	Shooting,
	Reloading, 
	Count // To keep track of the number of player states.
};

class PlayerStateManager : public jci::ICollision
{
public:
	inline static PlayerStateManager* Instance() { return m_instance == nullptr ? m_instance = new PlayerStateManager() : m_instance; }

	void Init(vec2 playerStartPosition, Gun* theGun);
	inline void Destroy() { delete m_instance; }

	void Update(float dt);

	/***
	* Get the position of the player.
	*
	*/
	inline vec2 GetPlayerPosition() const { return *m_player.m_position; }
	/***
	* Get the pointer of the player position.
	*
	*/
	inline vec2* GetPlayerPositionPointer() { return m_player.m_position; }
	/***
	* Get the player.
	*
	*/
	inline Player* GetPlayer() { return &m_player; }
	/***
	* Set the position of the player.
	* 
	*/
	inline void SetPlayerPosition(vec2 position) { *m_player.m_position = position; }
	/***
	* Set the players state.
	*
	*/
	void SetState(PlayerState state);	

private:
	PlayerStateManager();
	~PlayerStateManager();

	static PlayerStateManager* m_instance;

	Player m_player;

	std::vector<jci::IState*> m_playerStates;

	PlayerState m_state = PlayerState::Idle;

	// Player Collision Callbacks.
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final;
};