#include "stdafx.h"
#include "FileLoader.h"


bool FileLoader::CheckIfFileExists(std::string pFileName)
{
	struct stat buffer;
	return (stat(pFileName.c_str(), &buffer) == 0);
}

std::vector<double> FileLoader::LoadDataFromFile(std::string pFileName)
{
	std::vector<double> values;

	std::ifstream file(pFileName);
	while (!file.eof())
	{
		std::string line;
		file >> line;
		if (!line.empty())
			values.push_back(std::stod(line));
	}

	return values;
}

void FileLoader::SaveDataToFile(std::string pFileName, const std::vector<double> &pData)
{
	std::ofstream file(pFileName);
	for (unsigned int i = 0; i < pData.size(); ++i)
		file << pData[i] << std::endl;
}

std::string FileLoader::GetHrvFileName(std::string pDataFileName)
{
	for (unsigned int i = pDataFileName.size() - 1; i >= 0; --i)
	{
		if (pDataFileName[i] == '.')
		{
			pDataFileName.erase(i + 1, pDataFileName.size() - (i + 1));
			break;
		}
		else if ((pDataFileName[i] == '\\') ||
			(pDataFileName[i] == '/'))
			break;
	}
	pDataFileName.append("hrv");
	return pDataFileName;
}
