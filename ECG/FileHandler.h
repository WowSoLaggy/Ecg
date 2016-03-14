#pragma once

#ifndef FILEHANDLER_H
#define FILEHANDLER_H


// Class that loads data and saves it to file
class FileHandler
{
public:


	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// Main functions
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


	// Loads the data from the file with the given filename
	static std::vector<double> LoadDataFromFile(std::string pFileName);

	// Saves the given data to the file with the given filename
	static void SaveDataToFile(std::string pFileName, const std::vector<double> &pData);


	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// Auxiliary functions
	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


	// Checks if the file with the given name exists
	static bool CheckIfFileExists(std::string pFileName);

	// Returns the .hrv file name based on the given file name
	static std::string GetHrvFileName(std::string pDataFileName);
};


#endif // FILEHANDLER_H
