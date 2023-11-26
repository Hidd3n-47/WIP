#pragma once

/***
---------------- Assertions ----------------
*/
#ifdef _DEBUG
#define ASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }
#else
#define ASSERT(x, ...)
#endif

/***
---------------- Macros ----------------
*/
#ifdef _DEBUG
#define DLOG(x) Log::DebugLog(x)
#else
#define DLOG(x)
#endif

#include "PrimativeTypes.h"

/***
---------------- Entity and Components ----------------
*/
#define COMPONENT(x) \
friend class Entity; \
inline static uint16 GetIdMask() { return 1 << (int)x; } \
inline static std::string GetName() { return #x; }

namespace jci {
using entId = uint32;

constexpr uint8 MAX_COMPONENTS = 16;

const uint64 MAX_ENTITIES = 1 << (sizeof(entId) * 8 - MAX_COMPONENTS) - 1;
} // Namespace jci.