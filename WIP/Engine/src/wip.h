#pragma once

#include "PrimativeTypes.h"

// Macros.
#ifdef _DEBUG
#define ASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }

#define DLOG(x) jci::Log::DebugLog(x)

#define DOUT(x) jci::Engine::Instance()->dout += x + "\n"

#define DOUT_CLOSE() \
	IOManager::Instance()->SaveToFile(dout, "EngineLog/log.jci")

#else
#define ASSERT(x, ...)

#define DLOG(x)

#define DOUT(x)

#define DOUT_CLOSE()
#endif // _DEBUG


// ECS.
#define REGISTER_COMPONENT(x)													\
inline static uint16			GetIdMask()			{ return 1 << (int)x; }		\
inline static ComponentTypes	GetType()			{ return x;}				\
inline static std::string		GetName()			{ return #x; }				\
inline virtual void				SetId(entId id)		{ m_id = id; }				\
inline virtual entId			GetId() const		{ return m_id; }			\
inline virtual Entity*			GetEntity() final	{ return m_entity; }		

namespace jci {
using		entId					= uint32;
constexpr	entId invalid_id		= -1;
constexpr	uint8 MAX_COMPONENTS	= 16;
const		uint16 MAX_ENTITIES		= 1 << (sizeof(entId) * 8 - MAX_COMPONENTS) - 1;
} // Namespace jci.