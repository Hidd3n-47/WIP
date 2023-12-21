#pragma once

#include <FSM/IState.h>
#include <Time/Timer.h>

struct PlayerS;

class PlayerIdleState : public jci::IState
{
public:
	PlayerIdleState() = default;
	~PlayerIdleState() = default;

	virtual void OnStateEnter() final;
	virtual void OnStateUpdate(float dt) final;
	virtual void OnStateExit() final;
private:
	PlayerS* m_player = nullptr;
	uint32 m_idleTexture = 0;
};

class PlayerMovingState : public jci::IState
{
public:
	PlayerMovingState() = default;
	~PlayerMovingState() = default;

	virtual void OnStateEnter() final;
	virtual void OnStateUpdate(float dt) final;
	virtual void OnStateExit() final;
private:
	PlayerS* m_player = nullptr;
	uint32 m_movingTexture = 0;
};