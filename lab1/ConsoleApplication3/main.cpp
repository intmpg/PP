// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CThreadInverseMatrix.h"

int main()
{
	srand(time(0));
	
	size_t threads;
	size_t size;
	std::cout << "Enter matrix size : ";
	std::cin >> size;
	std::cout << "Enter number of threads : ";
	std::cin >> threads;
	CMatrix matrix(size);
	double matrixCreateTime = clock() / 1000.0;
	CThreadInverseMatrix invmatrix(matrix);
	double inverseMatrixCreateTime = clock() / 1000.0;
	std::cout << "One Thread Metod = " << inverseMatrixCreateTime - matrixCreateTime << std::endl;

	CThreadInverseMatrix invParallmatrix(matrix, threads);
	double inverseParallMatrixCreateTime = clock() / 1000.0;
	std::cout << " MultiThread Metod = " << inverseParallMatrixCreateTime - inverseMatrixCreateTime << std::endl;

/*	for (size_t i = 2; i < 17; i++)
	{	
		inverseMatrixCreateTime = clock() / 1000.0;
		CThreadInverseMatrix invParallmatrix(matrix, i);
		double inverseParallMatrixCreateTime = clock() / 1000.0;
		std::cout << i << " MultiThread Metod = " << inverseParallMatrixCreateTime - inverseMatrixCreateTime << std::endl;
		
	}*/

	return 0;
}

