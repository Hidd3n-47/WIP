#pragma once

#include <Engine/Collision/ICollision.h>
#include <Engine/FSM/IState.h>
#include <Game/Gun/Gun.h>

namespace jci
{
	class Entity;
}

// TODO (Isaac): Rename this to "Player" once you abstract Player.cpp and Player.h and can delete it.
struct PlayerS
{
	jci::Entity*	playerEntity	= nullptr;
	vec2*			position		= nullptr;
	jci::Entity*	m_knife			= nullptr;
	jci::Timer*		stabbin			= nullptr;
	jci::Timer*		dashCD			= nullptr;
	jci::Timer*		bulletCD		= nullptr;
	jci::Timer*		meleeCD			= nullptr;
	Gun*			m_equippedGun	= nullptr;
	uint32			m_blankTexture;
	uint32			m_knifeTexture;
	float			speed = 5.0f;
	float			m_width;
	float			m_height;
	float			time;
	bool			m_canFire = true;
	bool			m_canStab = true;
	bool			m_canDash = true;
	int				m_dashTime;
	int				m_stabTime;

	vec2 GetInputDirection();
};

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

	void Update(float dt);

	/***
	* Get the position of the player.
	*
	*/
	inline vec2 GetPlayerPosition() const { return *m_player.position; }
	/***
	* Get the pointer of the player position.
	*
	*/
	inline vec2* GetPlayerPositionPointer() { return m_player.position; }
	/***
	* Get the player.
	*
	*/
	inline PlayerS* GetPlayer() { return &m_player; }
	/***
	* Set the position of the player.
	* 
	*/
	inline void SetPlayerPosition(vec2 position) { *m_player.position = position; }
	/***
	* Set the players state.
	*
	*/
	void SetState(PlayerState state);

	

private:
	PlayerStateManager();
	~PlayerStateManager();

	static PlayerStateManager* m_instance;

	PlayerS m_player;

	std::vector<jci::IState*> m_playerStates;

	PlayerState m_state = PlayerState::Idle;

	// Player Collision Callbacks.
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit(jci::Entity* other) final;
};

