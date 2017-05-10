#include "AppLauncher.h"

CAppLauncher::CAppLauncher(size_t m_procNum, size_t m_itNum)
	: m_itNumber(m_itNum)
	, m_procNumber(m_procNum)
{
}

void CAppLauncher::Run()
{
	int failedProc = 0;
	WaitConnected();
	WaitMessages();
}

template <typename T>
std::string NumberToString(T number)
{
	std::ostringstream os;
	os << number;
	return os.str();

}

void CAppLauncher::SettingProcess(STARTUPINFO &si)
{
	si.dwFlags = STARTF_USESIZE | STARTF_USESHOWWINDOW;
	si.dwXSize = 500;
	si.dwYSize = 300;
	si.wShowWindow = SW_SHOW;
}

CAppLauncher::~CAppLauncher()
{
	for (size_t i = 0; i != m_procNumber; ++i)
	{
		CloseHandle(m_processesInformation[i].hProcess);
		CloseHandle(m_processesInformation[i].hThread);
	}
}

void CAppLauncher::WaitConnected()
{
	std::cout << "Waiting for connection " << m_procNumber << " customers" << std::endl;

	auto start = std::chrono::system_clock::now();
	std::vector<std::string> messages;

	CControlSocket controlSocket;
	controlSocket.CreateSocket();
	controlSocket.TuneSocket(11111, INADDR_ANY);
	controlSocket.WaitSend(messages, m_procNumber);

	bool divMode = true;
	if (m_itNumber % m_procNumber == 0)
	{
		divMode = false;
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time : " << diff.count() << std::endl;
	for (size_t it = 0; it < messages.size(); ++it)
	{
		auto mes = messages[it];
		unsigned numIter = m_itNumber / m_procNumber;
		if (divMode && it == messages.size() - 1)
		{
			numIter += m_itNumber % m_procNumber;
		}
		
		SendMessages(mes, NumberToString(numIter));
	}
}

void CAppLauncher::SendMessages(std::string number, const std::string & iterations)
{
	unsigned num = atoi(number.c_str());

	std::vector<std::string> messages;

	CControlSocket controlSocket;
	controlSocket.CreateSocket();
	controlSocket.TuneSocket(num, "localhost");
	controlSocket.SendMes(iterations);
}

void CAppLauncher::WaitMessages()
{
	auto start = std::chrono::system_clock::now();
	std::vector<std::string> messages;

	CControlSocket controlSocket;
	controlSocket.CreateSocket();
	controlSocket.TuneSocket(11111, INADDR_ANY);
	controlSocket.WaitSend(messages, m_procNumber);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time : " << diff.count() << std::endl;
	for (size_t it = 0; it < messages.size(); ++it)
	{
		std::cout << it + 1 << ") " << messages[it] << std::endl;
	}
	system("pause");
}
