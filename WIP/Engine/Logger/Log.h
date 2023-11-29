#pragma once


namespace jci {
/***
=========================================================================================
ERR_CODE:
	Error codes for engine.
=========================================================================================
*/
enum class ERR_CODE {
	DEFAULT = -1,
	SDL_ERROR = 1,
	FAILED_TO_OPEN_FILE = 2
};

/***
=========================================================================================
LOG:
	A static class responsible for logging messages to the sub-console.
=========================================================================================
*/
class Log
{
public:

	// Logs a message that will only show in debug mode.
	static void DebugLog(const std::string& msg);

	// Logs a warning message to the console.
	static void Warning(const std::string& warningMsg);

	// Logs a critical error message to the console. Critical errors does not exit the game.
	static void CriticalError(const std::string& errMsg, ERR_CODE errCode = ERR_CODE::DEFAULT);

	// Logs a fatal error message to the console. Fatal error message closes the game after message prompt.
	static void FatalError(const std::string& errMsg, ERR_CODE errCode = ERR_CODE::DEFAULT);
};

} // Namespace jci.