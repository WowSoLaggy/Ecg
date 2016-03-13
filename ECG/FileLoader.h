#pragma once

#ifndef FILELOADER_H
#define FILELOADER_H


class FileLoader
{
public:

	static bool CheckIfFileExists(std::string pFileName);
	static std::vector<double> LoadDataFromFile(std::string pFileName);
	static void SaveDataToFile(std::string pFileName, const std::vector<double> &pData);
	static std::string GetHrvFileName(std::string pDataFileName);
};


#endif // FILELOADER_H
