#pragma once
#include "src/pch.h"

namespace jci{

__interface IState
{
public:
	void OnStateEnter()		= 0;
	void OnStateUpdate()	= 0;
	void OnStateExit()		= 0;
};

} // Namespace