#include "pch.h"
#include "IOManager.h"

namespace jci {

IOManager* IOManager::m_instance = nullptr;

void IOManager::LoadTextFile(std::vector<std::string>& fileContents, const std::string& filePath)
{
	m_fileReadOnly.open(filePath.c_str(), std::ios::in);

	if (m_fileReadOnly.fail())
	{
		ASSERT(false, "Failed to open file.\nFile Path: " + filePath);
		Log::FatalError("Failed to open file.\nFile Path: " + filePath, ERR_CODE::FAILED_TO_OPEN_FILE);
	}

	std::string line;

	while (std::getline(m_fileReadOnly, line, '\n'))
	{
		fileContents.push_back(line);
	}

	m_fileReadOnly.close();
}

} // Namespace jci.