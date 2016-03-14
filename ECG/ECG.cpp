#include "stdafx.h"

#include "FileHandler.h"
#include "ecgannotation.h"


// Prints help if the input is invalid
void PrintUsage()
{
	std::cout << "Usage:" << std::endl;
	std::cout << "ECG.exe datafile.txt" << std::endl;
}


int main(int argc, char *argv[])
{
	// Check the input args

	if (argc != 2)
	{
		// Argument count mismatch
		PrintUsage();
		return 0;
	}

	// Check if the input file name is valid

	std::string dataFileName = std::string(argv[1]);
	if (!FileHandler::CheckIfFileExists(dataFileName))
	{
		std::cout << "Can't find input file." << std::endl;
		return 0;
	}

	// Load data and params

	int sr = 100;	// TODO: this should be loaded from the file (want to believe that it is frequency, but not sure)

	std::vector<double> magnitudes;
	magnitudes = FileHandler::LoadDataFromFile(dataFileName);

	// Process data (algorithm and all classes are taken "as is" from the original application)

	EcgAnnotation ann;
	int** qrsAnn = ann.GetQRS(magnitudes.data(), magnitudes.size(), sr, L"filters");
	if (!qrsAnn)
	{
		std::cout << "Failed to get QRS complexes. Make sure you have the \"filters\" directory in the ecg application dir." << std::endl;
		return 0;
	}

	int annNum = 0;
	int** ANN = ann.GetPTU(magnitudes.data(), magnitudes.size(), sr, L"filters", qrsAnn, ann.GetQrsNumber());     //find P,T waves
	if (ANN)
		annNum = ann.GetEcgAnnotationSize();
	else
	{
		ANN = qrsAnn;
		annNum = 2 * ann.GetQrsNumber();
	}

	std::vector<double> rrs;
	std::vector<int> rrsPos;
	if (!ann.GetRRseq(ANN, annNum, sr, &rrs, &rrsPos))
	{
		std::cout << "Failed to get heart rate. Check if the data file is correct." << std::endl;
		return 0;
	}

	// Save to the .hrv file

	std::string hrvFileName;
	hrvFileName = FileHandler::GetHrvFileName(dataFileName);
	FileHandler::SaveDataToFile(hrvFileName, rrs);

    return 0;
}
