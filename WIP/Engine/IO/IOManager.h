/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
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

	inline void Destroy() { delete m_instance; }

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
	/***
	* Saves text to a given file.
	* Content will be outputed and saved to file at the given path.
	*/
	void SaveToFile(const std::string& content, const std::string& filePath);

private:
	IOManager() = default;
	~IOManager() = default;

	static IOManager* m_instance;

	std::ifstream m_fileReadOnly;
	std::ofstream m_fileWrite;
};

} // Namespace jci.