// lab5 var 2

#include "stdafx.h"
#include <omp.h>
#include <iostream>
#include "Backer.h"

std::vector<int> FillArray(size_t size)
{
	std::vector<int>vec(size);
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		vec[i] = rand() % 100;
	}
	return vec;
}

void MergeTapes(std::vector<int> & v1, std::vector<int> & v2)
{
	while (v1.size() > 0)
	{
		v2.push_back(v1[0]);
		v1.erase(v1.begin());
	}
}

std::vector<int> ComposeTape(std::vector<int> tape1, std::vector<int> tape2)
{
	int size = tape1.size() + tape2.size();
	std::vector<int> tape3;
	while (tape1.size() > 0 && tape2.size() > 0)
	{
		int first = tape1[0];
		int second = tape2[0];
		if (first > second)
		{
			tape3.push_back(second);
			tape2.erase(tape2.begin());
		}
		else
		{
			tape3.push_back(first);
			tape1.erase(tape1.begin());
		}
	}
	MergeTapes(tape1, tape3);
	MergeTapes(tape2, tape3);
	return tape3;
}

std::vector<int> BackerSort(std::vector<int> & vec)
{
	size_t amount = 2;
	std::vector<int> vec1;
	std::vector<int> vec2;
	if (vec.size() > 0)
	{
		if (vec.size() > 2)
		{
			vec1.resize(vec.size() / 2);
			vec2.resize(vec.size() - vec.size() / 2);
			std::copy(vec.begin(), vec.begin() + vec.size() / 2, vec1.begin());
			std::copy(vec.begin() + vec.size() / 2, vec.end(), vec2.begin());

			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					vec1 = BackerSort(vec1);
				}
				else
				{
					vec2 = BackerSort(vec2);
				}
			}
		}
		else
		{
			if (vec.size() != 1)
			{
				if (vec[0] > vec[1])
				{
					std::swap(vec[0], vec[1]);
				}
			}
			return vec;
		}

		return ComposeTape(vec1, vec2);
	}
	return vec;
}


size_t GetSize() 
{
	std::cout << "Enter array size" << std::endl;
	size_t size;
	std::cin >> size;

	return size;
}

int main()
{
	size_t size = GetSize();
	size_t threads = GetThreads();

	FillArray(size);
	std::cout << "runtime = " << clock() / 1000.0 << std::endl;
	return 0;
}