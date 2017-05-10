#include "stdafx.h"
#include "BatcherAlgoritm.h"
#include <iterator>
#include <omp.h>
#include <chrono>

CBatcherAlgoritm::CBatcherAlgoritm(Vector const & listValues)
	:m_listValues(listValues)
{
}

Vector CBatcherAlgoritm::GetSortedList() const
{
	return m_listValues;
}

bool CBatcherAlgoritm::SortList()
{
	auto copyList = m_listValues;
	while (!IsUnit(copyList))
	{
		for (size_t i = 0; i != copyList.size(); ++i)
		{
			if (copyList.at(i).size() != 1)
			{
				Pair pair = BreakList(copyList.at(i));

				copyList.erase(copyList.begin() + i);
				copyList.insert(copyList.begin() + i, pair.first);
				copyList.insert(copyList.begin() + i + 1, pair.second);
			}
		}
	}
	MergeSort(copyList);
	m_listValues = copyList;

	return true;
}

void CBatcherAlgoritm::MergeSort(Vector & vec)
{
	Vector copyVec = vec;
	auto startParallel = std::chrono::system_clock::now();
	while (copyVec.size() != 1)
	{
		Vector resultVec;
		#pragma omp parallel for
		for (int k = 0; k < copyVec.size(); k += 2)
		{
			std::vector<int> interResult;
			auto vecFirst = copyVec.at(k);

			if (k + 1 >= copyVec.size())
			{
				interResult.resize(vecFirst.size());
				std::copy(vecFirst.begin(), vecFirst.end(), interResult.begin());
				
			}
			else
			{
				int j = 0;
				for (int i = 0; i != vecFirst.size(); ++i)
				{
					auto vecSecond = copyVec.at(k + 1);

					for (; j != vecSecond.size(); ++j)
					{
						auto headFirst = vecFirst.at(i);
						auto headSecond = vecSecond.at(j);
						if (headFirst <= headSecond)
						{
							interResult.push_back(headFirst);
							break;
						}
						else
							interResult.push_back(headSecond);
					}

					if (i + 1 == vecFirst.size())
						std::copy(vecSecond.begin() + j, vecSecond.end(), std::back_inserter(interResult));
					if (j + 1 > vecSecond.size())
					{
						std::copy(vecFirst.begin() + i, vecFirst.end(), std::back_inserter(interResult));
						break;
					}

				}
			}
			#pragma omp critical
			{
				resultVec.push_back(interResult);
			}
		}
		copyVec = resultVec;
	}
	vec = copyVec;
	auto endParallel = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = endParallel - startParallel;
	std::cout << "Time: " << diff.count() << std::endl;
}

Pair CBatcherAlgoritm::BreakList(std::vector<int> const &list)
{
	size_t sizeHalf = list.size() / 2;

	std::vector<int> firstHalf(sizeHalf);
	std::vector<int> secondHalf(list.size() - sizeHalf);

	std::copy(list.begin(), list.begin() + sizeHalf, firstHalf.begin());
	std::copy(list.begin() + sizeHalf, list.end(), secondHalf.begin());

	return { firstHalf, secondHalf };
}

bool CBatcherAlgoritm::IsUnit(Vector const &vec)
{
	for (auto el : vec)
	{
		if (el.size() > 1)
			return false;
	}
	return true;
}
