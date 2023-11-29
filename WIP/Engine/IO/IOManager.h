#pragma once

#include "Logger/Log.h"

/***
=========================================================================================
IO_MANAGER:
	IO Manager is a singleton used to load a file into a vector of strings.
=========================================================================================
*/
namespace jci {

class IOManager
{
public:
	inline static IOManager* Instance() { return m_instance == nullptr ? m_instance = new IOManager() : m_instance; }

	/***
	* Load a given text file at given file path and stores contents in a vector.
	* Vector stores each line seperately.
	*/
	void LoadTextFile(std::vector<std::string>& fileContents, const std::string& filePath);
	/***
	* Load a given text file at given file path and stores contents in a vector.
	* Returns a single string with '\n' characters for new line.
	*/
	std::string LoadTextFile(const std::string& filePath);

private:
	IOManager() = default;
	inline ~IOManager() { delete m_instance; }

	static IOManager* m_instance;

	std::ifstream m_fileReadOnly;
};

} // Namespace jci.