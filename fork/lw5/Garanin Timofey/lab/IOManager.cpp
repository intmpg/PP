#include "stdafx.h"
#include "IOManager.h"
#include <algorithm>
#include <iterator>

using namespace std;

CIOManager::CIOManager(std::string const & inFile, std::string const & outFile)
	: m_inputFileName(inFile)
	, m_outputFileName(outFile)
{
}

Vector CIOManager::ReadDataFromFile()
{
	ifstream file(m_inputFileName);
	if (!file)
	{
		std::cerr << "Input file not found" << std::endl;
		throw std::runtime_error("file not found");
	}

	Vector values;
	string inputString;
	vector<int> listValues;
	while (getline(file, inputString))
	{
		stringstream str(inputString);
		while (!str.eof())
		{
			string newVal;
			str >> newVal;
			listValues.push_back(atoi(newVal.c_str()));
		}
	}
	values.push_back(listValues);
	return values;
}

void CIOManager::OutputDataToFile(Vector const & vec)
{
	std::ofstream stream(m_outputFileName);
	for (auto el : vec.at(0))
	{
		stream << el << " ";
	}
}
