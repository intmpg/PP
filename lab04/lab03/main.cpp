#include "stdafx.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <vector>
#include <string>
#include "ControlSocket.h"
#include "ClientManipulation.h"

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "wsock32.lib")


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error! Usage program.exe <ip_server>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string ipServer = std::string(argv[1]);
	
	CClientManipulation clientMan;
	clientMan.Run(ipServer);
		

	system("pause");
}