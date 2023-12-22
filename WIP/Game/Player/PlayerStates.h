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

class PlayerDashingState : public jci::IState
{
public:
	PlayerDashingState() = default;
	~PlayerDashingState() = default;

	virtual void OnStateEnter() final;
	virtual void OnStateUpdate(float dt) final;
	virtual void OnStateExit() final;
private:
	PlayerS* m_player = nullptr;
	uint32 m_movingTexture = 0;
};

class PlayerMeleeState : public jci::IState
{
public:
	PlayerMeleeState() = default;
	~PlayerMeleeState() = default;

	virtual void OnStateEnter() final;
	virtual void OnStateUpdate(float dt) final;
	virtual void OnStateExit() final;
private:
	PlayerS* m_player = nullptr;
	uint32 m_movingTexture = 0;
};

class PlayerShootingState : public jci::IState
{
public:
	PlayerShootingState() = default;
	~PlayerShootingState() = default;

	virtual void OnStateEnter() final;
	virtual void OnStateUpdate(float dt) final;
	virtual void OnStateExit() final;
private:
	PlayerS* m_player = nullptr;
	uint32 m_movingTexture = 0;
};