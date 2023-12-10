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
	
	inline void Update() { m_state->OnStateUpdate(); }

	inline void ChangeState(IState* newState) { m_state = newState; }
private:
	IState* m_state;
};

} // Namespace jci.

/***
* QUESTION: STATE TREES
*	HOW TO DEFINE STATE TREES?
*		LINKED LIST?
*		WHAT ABOUT MULITPLE LINKS?
* 
*	CUSTOM LINKED LIST WITH A VECTOR OF NODES?
* 
*	WHAT ABOUT PARSING/SETTING THE TREE??
* 
*/