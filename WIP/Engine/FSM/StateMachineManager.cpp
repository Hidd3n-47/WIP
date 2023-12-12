#include "pch.h"
#include "StateMachineManager.h"

#include "IStateMachine.h"

namespace jci {

StateMachineManager* StateMachineManager::m_instance = nullptr;

void StateMachineManager::Update()
{
	for (IStateMachine* stateMachine : m_stateMachines)
	{
		stateMachine->Update();
	}
}

} // Namespace jci.