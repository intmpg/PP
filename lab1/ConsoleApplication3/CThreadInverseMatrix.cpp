#include "stdafx.h"
#include "CThreadInverseMatrix.h"

void  StartParall(CThreadInverseMatrix * matr, size_t num)
{
	matr->DoInverseMatrix(num, num+1);
}

CThreadInverseMatrix::CThreadInverseMatrix(CMatrix & const matrix)
{
	m_eMatrix = matrix.GetEMatrix();
	m_matrix = matrix.GetMatrix();
	n = matrix.GetSize();
	DoInverseMatrix(0, n);
};

CThreadInverseMatrix::CThreadInverseMatrix(CMatrix & const matrix, int threadNumber)
{
	m_eMatrix = matrix.GetEMatrix();
	m_matrix = matrix.GetMatrix();
	n = matrix.GetSize();
	maxThread = threadNumber;
	DoParallInverseMatrix();
};


CThreadInverseMatrix::~CThreadInverseMatrix()
{
};


void CThreadInverseMatrix::DoInverseMatrix(size_t start, size_t finish)
{
	for (size_t diagonal = start; diagonal < finish; diagonal++)
	{
		
		if (m_matrix[diagonal][diagonal] != 1)
		{
			for (size_t k = diagonal + 1; k < n; k++)
			{
				m_matrix[diagonal][k] = m_matrix[diagonal][k] / m_matrix[diagonal][diagonal];
			}
			for (size_t k = 0; k < n; k++)
			{
				m_eMatrix[diagonal][k] = m_eMatrix[diagonal][k] / m_matrix[diagonal][diagonal];
			}
			m_matrix[diagonal][diagonal] /= m_matrix[diagonal][diagonal];
		}
		for (size_t i = diagonal + 1; i < n; i++)
		{
			double storage = m_matrix[i][diagonal];

			for (size_t j = diagonal; j < n; j++)
			{
				m_matrix[i][j] -= m_matrix[diagonal][j] * storage;
			}
			for (size_t j = 0; j < n; j++)
			{
				m_eMatrix[i][j] -= m_eMatrix[diagonal][j] * storage;
			}
		}
		for (size_t i = 0; i < diagonal; i++)
		{
			double storage = m_matrix[i][diagonal];

			for (size_t j = diagonal; j < n; j++)
			{
				m_matrix[i][j] -= m_matrix[diagonal][j] * storage;
			}
			for (size_t j = 0; j < n; j++)
			{
				m_eMatrix[i][j] -= m_eMatrix[diagonal][j] * storage;
			}
		}
	}
}

void CThreadInverseMatrix::DoParallInverseMatrix()
{	
	thrs.resize(maxThread);
	size_t currentThread = 0;
	for (size_t i = 0; i < n; i++)
	{
		thrs[currentThread] = std::thread(StartParall, this, i);
		currentThread++;
		if (currentThread == maxThread)
		{
			for (size_t j = 0; j < maxThread; j++)
			{
				thrs[j].join();
			}
			currentThread = 0;
		}
	}

	for (size_t j = 0; j < currentThread; j++)
	{
		thrs[j].join();
	}
}