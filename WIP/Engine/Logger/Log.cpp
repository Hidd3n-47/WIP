#include "pch.h"
#include "Log.h"

#include "src/Engine.h"

namespace jci {

void Log::DebugLog(const std::string& msg)
{
#ifdef _DEBUG
	printf("\033[1;36m%s\033[0;36m", "Debug: ");
	printf("%s\n", msg.c_str());
	printf("\033[0;37m");
#endif
}

void Log::Warning(const std::string& warningMsg)
{
	printf("\033[0;33m%s\033[0;33m", "Warning:\n");
	printf("%s\n", warningMsg.c_str());
	printf("\033[0;37m");
}

void Log::CriticalError(const std::string& errMsg, ERR_CODE errCode)
{
	printf("\033[1;35m%s\033[0;35m", "Critical Error:\n");
	printf("%s\nError Code: %d\n", errMsg.c_str(), errCode);
	printf("\033[0;37m");
}

void Log::FatalError(const std::string& errMsg, ERR_CODE errCode)
{
	printf("\033[1;31m%s\033[0;31m", "Fatal Error:\n");
	printf("%s\nError Code: %d\n", errMsg.c_str(), errCode);
	printf("\033[0;37m");

	if (errCode == ERR_CODE::SDL_ERROR)
	{
		printf("%s\n", SDL_GetError());
	}

	system("PAUSE");

	Engine::Instance()->StopRunning();
}

} // Namespace jci.