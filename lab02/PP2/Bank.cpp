#include "Bank.h"


CBank::CBank(PrimitiveSynchronize type)
	: m_primitiveSynchronizeType(type)
	, m_totalBalance(0)
	, m_clients(std::vector<CBankClient>())
{
	selectPrimitiveSynchronize();
}

void CBank::selectPrimitiveSynchronize()
{
	switch (m_primitiveSynchronizeType)
	{
	case PrimitiveSynchronize::CriticalSection:
		InitializeCriticalSection(&m_criticalSection);
		//VOID InitializeCriticalSection
		//(
		//	LPCRITICAL_SECTION lpCriticalSection
		//	// указатель на переменную критическая секция
		//);
		break;
	case PrimitiveSynchronize::Mutex:
		m_hMutex = CreateMutex(NULL, false, NULL);
		//HANDLE CreateMutex
		//(
		//	LPSECURITY_ATTRIBUTES lpMutexAttributes,	// атрибут безопастности
		//	BOOL bInitialOwner,			// флаг начального владельца
		//	LPCTSTR lpName				// имя объекта
		//);
		break;
	case PrimitiveSynchronize::Semaphore:
		m_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		//HANDLE CreateSemaphore
		//(
		//	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,	// атрибут доступа
		//	LONG lInitialCount,			// инициализированное начальное состояние счетчика
		//	LONG lMaximumCount,			// максимальное количество обращений
		//	LPCTSTR lpName				// имя объекта
		//);
		break;
	case PrimitiveSynchronize::Event:
		m_hEvent = CreateEvent(NULL, true, false, NULL);
		//HANDLE CreateEvent
		//(
		//	LPSECURITY_ATTRIBUTES lpEventAttributes,	// атрибут защиты
		//	BOOL bManualReset,				// тип сброса TRUE - ручной
		//	BOOL bInitialState,			// начальное состояние TRUE - сигнальное
		//	LPCTSTR lpName				// имя обьекта
		//);
		break;
	}
}



CBank::~CBank()
{
	switch (m_primitiveSynchronizeType)
	{
	case PrimitiveSynchronize::CriticalSection:
		DeleteCriticalSection(&m_criticalSection);
		break;
	case PrimitiveSynchronize::Mutex:
		CloseHandle(&m_hMutex);
		break;
	case PrimitiveSynchronize::Semaphore:
		CloseHandle(m_hSemaphore);
		break;
	case PrimitiveSynchronize::Event:
		CloseHandle(m_hEvent);
		break;
	}
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	m_clients.push_back(CBankClient(this, clientId));
	return &m_clients.back();
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	if (totalBalance < 0)
	{
		std::cout << std::endl << std::endl;
		std::cout << "ERROR in operation" << std::endl;
		std::cout << "Total balance = " << GetTotalBalance() << std::endl;
		std::cout << "Value = " << value << std::endl;
		std::cout << "Set Value = " << totalBalance << std::endl;
		std::cout << "Balance not must be less zero!!!" << std::endl;
		return;
	}
	SetTotalBalance(totalBalance);
}

void CBank::CreateThreads()
{
	for (size_t index = 0; index < m_clients.size(); ++index)
	{
		auto & client = m_clients[index];
		m_threads.push_back(CreateThread(NULL, 0, &client.ThreadFunction, &client, CREATE_SUSPENDED, NULL));
	}
}

void CBank::WaitThreads()
{
	for (auto & thread : m_threads)
	{
		ResumeThread(thread);
	}
	WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}



int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	switch (m_primitiveSynchronizeType)
	{
	case PrimitiveSynchronize::CriticalSection:
		EnterCriticalSection(&m_criticalSection);// указатель на переменную критическая секция
		m_totalBalance = value;
		LeaveCriticalSection(&m_criticalSection);
		break;
	case PrimitiveSynchronize::Mutex:
		WaitForSingleObject(m_hMutex, INFINITE);
		m_totalBalance = value;
		ReleaseMutex(m_hMutex);
		break;
	case PrimitiveSynchronize::Semaphore:
		WaitForSingleObject(m_hSemaphore, INFINITE);//m_hSemaphore -указатель ,time
		m_totalBalance = value;
		ReleaseSemaphore(m_hSemaphore, 1, NULL);
		//BOOL ReleaseSemaphore
		//(
		//	HANDLE hSemaphore,		// хенд семафора
		//	LONG lReleaseCount, 	// на сколько изменять счетчик
		//	LPLONG lpPreviousCount	// предыдущее значение
		//);
		break;
	case PrimitiveSynchronize::Event:
		SetEvent(m_hEvent);
		m_totalBalance = value;
		ResetEvent(m_hEvent);
		break;
	default:
		m_totalBalance = value;
		break;
	}
}

void CBank::SomeLongOperations()
{
	Sleep(GetSleepDuration());
}

unsigned int CBank::GetSleepDuration()
{
	return rand() % 100;
}