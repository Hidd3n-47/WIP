#pragma once

// Macros.
#ifdef _DEBUG
#define ASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }

#define DLOG(x) Log::DebugLog(x);

#define DOUT(x) Engine::Instance()->dout += x + "\n";

#define DOUT_CLOSE() \
	IOManager::Instance()->SaveToFile(dout, "EngineLog/log.jci");

#else
#define ASSERT(x, ...)

#define DLOG(x)

#define DOUT(x)
#endif // _DEBUG
	
#define COMPONENT(x) \
inline static uint16 GetIdMask() { return 1 << (int)x; } \
inline static std::string GetName() { return #x; }