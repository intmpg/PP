#pragma once


class CIOManager
{
public:
	CIOManager(std::string const &inFile, std::string const &outFile);
	Vector ReadDataFromFile();
	void OutputDataToFile(Vector const &vec);
private:
	std::string m_inputFileName;
	std::string m_outputFileName;
};