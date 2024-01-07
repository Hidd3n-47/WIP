/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "Random.h"

namespace jci
{

Random* Random::m_instance = nullptr;

void Random::Init() 
{ 
	m_randomEngine = std::mt19937(time(nullptr)); 
}

float Random::Rand()
{ 
	return (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32>::max(); 
}

} // Namespace jci.