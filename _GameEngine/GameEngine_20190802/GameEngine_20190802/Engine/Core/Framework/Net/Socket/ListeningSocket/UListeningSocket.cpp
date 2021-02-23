#include "UListeningSocket.h"

UListeningSocket::UListeningSocket() :
	InternetAddress(),
	MaxQueueNum(0),
	Port(0)
{
}

UListeningSocket::~UListeningSocket()
{
	closesocket(FD);
}

void UListeningSocket::Init(unsigned int _MaxQueueNum)
{
	FD = socket(AF_INET, SOCK_STREAM, 0);
	if (FD == INVALID_SOCKET) return;

	std::cout << "Listening socket init success" << std::endl;
	MaxQueueNum = _MaxQueueNum;
}

void UListeningSocket::Bind(unsigned int _Port)
{
	InternetAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	InternetAddress.sin_family = AF_INET;
	InternetAddress.sin_port = htons(_Port);

	int Result = bind(FD, (SOCKADDR*)& InternetAddress, sizeof SOCKADDR);
	if (Result != 0) return;

	Port = _Port;
	std::cout << "Bind success." << std::endl;
}

void UListeningSocket::Listen()
{
	if (MaxQueueNum <= 0) return;
	
	int Result = listen(FD, MaxQueueNum);
	if (Result != 0) return;

	std::cout << "Listen succees" << std::endl;
}
