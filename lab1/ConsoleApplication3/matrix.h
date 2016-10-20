#include "stdafx.h"

class CMatrix
{
public:
	CMatrix(size_t size);
	~CMatrix();
	std::vector<std::vector<double>> GetMatrix();
	std::vector<std::vector<double>> GetEMatrix();
	void WriteMatrix(std::vector<std::vector<double>> m);
	size_t GetSize();
private:
	void FillMatrix();
	bool GetDeterm();
	std::vector<std::vector<double>> m_matrix;
	std::vector<std::vector<double>> m_eMatrix;
	size_t n;
};