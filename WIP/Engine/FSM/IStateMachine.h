#pragma once
#include "pch.h"

#include "IState.h"

namespace jci {

class IStateMachine
{
public:
	inline IStateMachine() : m_state(nullptr) { /* Empty. */ }
	inline IStateMachine(IState* startinState) : m_state(startinState) { m_state->OnStateEnter(); }
	virtual ~IStateMachine() = default;
	
	inline void Update(float dt) { m_state->OnStateUpdate(dt); }

	inline void ChangeState(IState* newState) { m_state = newState; }
private:
	IState* m_state;
};

} // Namespace jci.