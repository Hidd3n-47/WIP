#pragma once

#include "PrimativeTypes.h"

// Macros.
#ifdef _DEBUG
#define ASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }

#define Dbg_Render(x) RendererManager::Instance()->AddQuadToQueue(x)
#define Dbg_Render_Remove(x) RendererManager::Instance()->RemoveQuadFromQueue(x)

#define DLOG(x) jci::Log::DebugLog(x)

#define DOUT(x) jci::Engine::Instance()->dout += x + "\n"

#define DOUT_CLOSE() \
	IOManager::Instance()->SaveToFile(dout, "EngineLog/log.jci")

#else
#define ASSERT(x, ...)

#define Dbg_Render(x) 
#define Dbg_Render_Remove(x) 

#define DLOG(x)

#define DOUT(x)

#define DOUT_CLOSE()
#endif // _DEBUG

// Math defines.
#define PI 3.14159265358979323846264338327950288

// ECS.
#define REGISTER_COMPONENT(x)													\
friend class ComponentManager;													\
inline static uint16			GetIdMask()			{ return 1 << (int)x; }		\
inline static ComponentTypes	GetType()			{ return x;}				\
inline static std::string		GetName()			{ return #x; }				\
inline virtual void				SetId(entId id)		{ m_id = id; }				\
inline virtual entId			GetId() const		{ return m_id; }			\
inline virtual Entity*			GetEntity() final	{ return m_entity; }		\
inline virtual ComponentTypes	GetComponentType() const final { return x;}

__interface IProperties {};

namespace jci {
using		entId					= uint32;
constexpr	entId invalid_id		= -1;
constexpr	uint8 MAX_COMPONENTS	= 16;
const		uint16 MAX_ENTITIES		= 1 << (sizeof(entId) * 8 - MAX_COMPONENTS) - 1;
} // Namespace jci.