#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

void PrintHelp()
{
	std::cout << "Helper" << std::endl;
	std::cout << "First parametr - amount clients" << std::endl;
	std::cout << "Second parametr - type primitive synchronization" << std::endl;
	std::cout << "Third parametr - call help" << std::endl;
	std::cout << std::endl;
	std::cout << "Second parametr type:" << std::endl;
	std::cout << "1 - critical section" << std::endl;
	std::cout << "2 - mutex" << std::endl;
	std::cout << "3 - semaphore" << std::endl;
	std::cout << "4 - event" << std::endl;
}

bool wasHelpParametr(int argc, char * argv[])
{
	std::string callHelp = "/?";
	if (argc == 4)
	{
		if (argv[3] == callHelp)
		{
			return true;
		}
	}
	return false;
}

bool isRightPrimitiveSynchronize(char * argv[], PrimitiveSynchronize &type)
{
	int value = atoi(argv[2]);
	switch (value)
	{
	case 1:
		type = PrimitiveSynchronize::CriticalSection;
		break;
	case 2:
		type = PrimitiveSynchronize::Mutex;
		break;
	case 3:
		type = PrimitiveSynchronize::Semaphore;
		break;
	case 4:
		type = PrimitiveSynchronize::Event;
		break;
	default:
		return false;
	}	
	return true;
}

int main(int argc, char * argv[])
{
	if (argc != 3 && argc != 4)
	{
		std::cout << "Incorrect amount arguments!";
		PrintHelp();
		return 1;
	}
	if (wasHelpParametr(argc, argv))
	{
		PrintHelp();
	}
	size_t quantityClients = size_t(atoi(argv[1]));
	PrimitiveSynchronize type;
	if (!isRightPrimitiveSynchronize(argv, type))
	{
		std::cout << "Incorrect second argument!";
		PrintHelp();
		return 1;
	}
	CBank bank(type);
	for (size_t index = 0; index < quantityClients; ++index)
	{
		bank.CreateClient();
	}
	bank.CreateThreads();	
	bank.WaitThreads();

    return 0;
}