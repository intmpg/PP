#pragma once

typedef std::pair<std::vector<int>, std::vector<int>> Pair;

class CBatcherAlgoritm
{
public:
	CBatcherAlgoritm(Vector const &listValues);
	Vector GetSortedList() const;
	bool SortList();
private:
	void MergeSort(Vector &vec);
	Pair BreakList(std::vector<int> const &list);
	bool IsUnit(Vector const &vec);
	Vector m_listValues;

};