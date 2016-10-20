#include "stdafx.h"
#include "matrix.h"

class CThreadInverseMatrix
{
public:
	CThreadInverseMatrix(CMatrix & const matrix);
	CThreadInverseMatrix(CMatrix & const matrix, int threadNumber);
	~CThreadInverseMatrix();
	void DoInverseMatrix(size_t start, size_t finish);
	void DoParallInverseMatrix();
private:
	std::vector<std::vector<double>> m_matrix;
	std::vector<std::vector<double>> m_eMatrix;
	int maxThread;
	std::vector<std::thread> thrs;
	size_t n;
};