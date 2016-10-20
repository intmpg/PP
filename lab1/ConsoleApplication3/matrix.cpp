#include "stdafx.h"
#include "matrix.h"

CMatrix::CMatrix(size_t size)
{
	n = size;
	FillMatrix();
	if (!GetDeterm())
	{
		while (GetDeterm() != true)
			FillMatrix();
	}
}

size_t CMatrix::GetSize()
{
	return n;
}

CMatrix::~CMatrix()
{
};

bool CMatrix::GetDeterm()
{
	int l;
	double d;
	double sum11 = 1, sum12 = 0, sum21 = 1, sum22 = 0;

	for (int i = 0;i < n; i++)
	{
		sum11 = 1; l = 2 * n - 1 - i; sum21 = 1;
		for (int j = 0; j < n ; j++)
		{
			sum21 *= m_matrix[j][l % n];
			l--;
			sum11 *= m_matrix[j][(j + i) % (n)];
		}
		sum22 += sum21;
		sum12 += sum11;
	}
	d = sum12 - sum22;

	if (d != 0)
		return true;
	else
		return false;
}

void CMatrix::FillMatrix()
{
	m_matrix.resize(n);
	for (int i = 0; i < n; i++)
		m_matrix[i].resize(n);

	m_eMatrix.resize(n);
	for (int i = 0; i < n; i++)
		m_eMatrix[i].resize(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m_matrix[i][j] = rand() % 4 + 1;
		}
	}
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		m_eMatrix[i][j] = 1;
		j += 1;
	}
}

std::vector<std::vector<double>> CMatrix::GetEMatrix()
{
	return m_eMatrix;
}

void CMatrix::WriteMatrix(std::vector<std::vector<double>> m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m[i][j] = m[i][j];
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<double>> CMatrix::GetMatrix()
{
	return m_matrix;
}
