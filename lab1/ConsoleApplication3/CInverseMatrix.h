#include "stdafx.h"
#include "matrix.h"

class CInverseMatrix
{
public:
	CInverseMatrix(CMatrix & const matrix);
	CInverseMatrix(CMatrix & const matrix, int threadNumber);
	~CInverseMatrix();
	void GetMatrixSize(CMatrix & const matrix);
	void DoInverseMatrix(size_t start, size_t finish);
	void DoParallInverseMatrix();

private:
	std::vector<std::vector<double>> m_matrix;
	std::vector<std::vector<double>> m_eMatrix;
	int maxThread;
	std::vector<std::thread> thrs;
	size_t n;
};