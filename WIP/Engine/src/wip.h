#pragma once

// Assertions.
#ifdef _DEBUG
#define ASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }
#else
#define ASSERT(x, ...)
#endif

// Macros.
#ifdef _DEBUG
#define DLOG(x) Log::DebugLog(x)
#else
#define DLOG(x)
#endif