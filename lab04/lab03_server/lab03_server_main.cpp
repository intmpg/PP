#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "AppLauncher.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Error! Usage program.exe <processes number> <iterations number>" << std::endl;
		return EXIT_FAILURE;
	}

	unsigned clientsNum = atoi(argv[1]);
	unsigned iterationsNum = atoi(argv[2]);
	CAppLauncher launcher(clientsNum, iterationsNum);
	launcher.Run();
	return 0;
	system("pause");
}

