#pragma once

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

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "wsock32.lib")


class CClientManipulation
{
public:
	CClientManipulation();
	~CClientManipulation();
	bool Run(const std::string & processName);

private:
	int RandomRangeFloatInClient(int a, int b);
	bool ConnectToServer(unsigned Nmax, std::string const & processName);
	bool ConnectToClient(unsigned Nmax);
	void TransmitDataToServer(size_t Nmax, double Pi, std::string const & processName);
	double GetPi(size_t iterationsNumber);

private:
	int m_radius = 10;
	int m_iterations = 0;
};

