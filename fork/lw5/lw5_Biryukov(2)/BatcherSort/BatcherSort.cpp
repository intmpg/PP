// CBatcherSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BatcherSort.h"
#include <omp.h>

std::vector<int> CBatcherSort::FillArray(size_t size)
{
	std::vector<int>vec(size);
	srand(time(0));
	for (unsigned int i = 0; i < size; i++)
	{
		vec[i] = rand() % 100;
	}
	return vec;
}

void CBatcherSort::MergeTapes(std::vector<int>& v1, std::vector<int>& v2)
{
	while (v1.size() > 0)
	{
		v2.push_back(v1[0]);
		v1.erase(v1.begin());
	}
}

std::vector<int> CBatcherSort::ComposeTape(std::vector<int> tape1, std::vector<int> tape2)
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

std::vector<int> CBatcherSort::SortProcess(std::vector<int>& vec)
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

			#pragma omp parallel num_threads(amount)
			#pragma omp 
			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					vec1 = SortProcess(vec1);
				}
				else
				{
					vec2 = SortProcess(vec2);
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

size_t CBatcherSort::GetSize()
{
	std::cout << "Enter array size" << std::endl;
	std::cin >> size;
	return size;
}

int main()
{
	CBatcherSort batcher;
	clock_t t = clock();

	#pragma omp parallel num_threads(threads)
	#pragma omp for schedule(dynamic, batcher.GetSize() / threads)

	std::vector <int> vec = batcher.SortProcess(batcher.FillArray(batcher.GetSize()));
	std::cout << "runtime = " << (clock() - t) / 1000.0 << std::endl;
	return 0;
}

