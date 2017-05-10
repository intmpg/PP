#pragma once
#include <Windows.h>
#include "Bank.h"

class CBank;

class CBankClient
{
public:
	unsigned GetId();
private:
	CBankClient(CBank *bank, unsigned id);
	static unsigned GetSleepDuration(CBankClient *client);
	static unsigned GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	friend CBank;

private:
	CBank *m_bank;
	unsigned m_id;
};