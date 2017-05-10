#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "BankClient.h"

enum PrimitiveSynchronize
{
		CriticalSection = 1
	,	Mutex
	,	Semaphore
	,	Event
};

class CBankClient;

class CBank
{
public:
	CBank(PrimitiveSynchronize type);
	~CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	void WaitThreads();
	void CreateThreads();
private:
	std::vector<CBankClient> m_clients;
	std::vector<HANDLE> m_threads;
	int m_totalBalance;
	PrimitiveSynchronize m_primitiveSynchronizeType;
	CRITICAL_SECTION m_criticalSection;
	HANDLE m_hMutex;
	HANDLE m_hSemaphore;
	HANDLE m_hEvent;
private:
	void selectPrimitiveSynchronize() ;
	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations();
	unsigned int GetSleepDuration();
};