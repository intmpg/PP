// lab.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BatcherAlgoritm.h"
#include "IOManager.h"


int main()
{
	CIOManager manager("Input.txt", "output.txt");
	CBatcherAlgoritm algoritm(manager.ReadDataFromFile());
	algoritm.SortList();
	manager.OutputDataToFile(algoritm.GetSortedList());
    return 0;
}

