#include "ULocalSocket.h"

ULocalSocket::ULocalSocket() :
	SocketFD(0),
	bAvailable(false),
	SelectInterval({0, 0})
{
}

ULocalSocket::~ULocalSocket()
{
	closesocket(SocketFD);
}

void ULocalSocket::_Send()
{
	if (!IsValid()) return;

	if (Out.size() < 1) return;

	for (auto It = Out.begin(); It != Out.end(); ++It)
	{
		if(_CoreSend(**It))
		{
		}
	}
	Out.clear();
}

void ULocalSocket::_Receive()
{
	std::vector<std::string> Contents;
	if (_CoreReceive(Contents))
	{
		for (auto& Elem : Contents)
		{
			std::shared_ptr<std::string> Content = std::make_shared<std::string>();
			*Content = Elem;
			In.push_back(Content);
		}
		Contents.clear();
	}
}

bool ULocalSocket::_CoreSend(const std::string& Content)
{
	FD_ZERO(&WriteSet);
	FD_SET(SocketFD, &WriteSet);
	int Ret = select(0, NULL, &WriteSet, NULL, &SelectInterval);

	if (Ret <= 0) return false;

	/*char* FinalContent = new char[Content.size() + 1];
	strcpy(FinalContent, Content.c_str());
	FinalContent[Content.size()] = '\0';*/
	
	int Result = send(SocketFD, Content.c_str(), Content.size() + 1, 0);
	std::cout << Result << std::endl << std::endl;

	/*delete[] FinalContent;*/

	if (Result > 0)
	{
		if (Result == Content.size() + 1)
		{
			//std::cout << "The data has been pushed into the protocol buffer." << std::endl;
			return true;
		}

		std::cout << "The data has not been pushed into the protocol buffer compeletely." << std::endl;
		return false;
	}

	else if (Result == 0)
	{
		std::cout << "The remote spot has closed it's socket." << std::endl;
		return false;
	}

	else if (Result == SOCKET_ERROR)
	{
		std::cout << "Sending failed with: " << WSAGetLastError() << std::endl;

		// These errors will not cause socket closing.
		// Next tick will try to send again.
		if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
			return false;
			
		std::cout << "A terrible error hanppend." << std::endl;
		// However other errors will cause the socket closing.
		bAvailable = false;
		closesocket(SocketFD);
		return false;
	}

	std::cout << "Unkown error" << std::endl;
	return false;
}

bool ULocalSocket::_CoreReceive(std::vector<std::string>& Contents)
{
	if (!IsValid()) return false;
	//1024Byte - 1KB   MAX 4098Byte
	
	FD_ZERO(&ReadSet);
	FD_SET(SocketFD, &ReadSet);
	int Ret = select(0, &ReadSet, NULL, NULL, &SelectInterval);
	if (Ret <= 0) return false;

	char Buffer[1024] = { '\0' };
	int Result = recv(SocketFD, Buffer, 1024, 0);

	if (Result > 0)
	{
		std::vector<char> InBuffer;
		size_t vectorSize = InBuffer.size();
		InBuffer.resize(vectorSize + Result);
		memcpy(InBuffer.data() + vectorSize * sizeof(char), Buffer, Result * sizeof(char));
		
		RecvBuffer.append(InBuffer.begin(), InBuffer.end());
		
		while (RecvBuffer.find('\0') != std::string::npos)
		{
			std::string Content;
			size_t Index = RecvBuffer.find('\0', 0);
			Content.append(RecvBuffer.begin(), RecvBuffer.begin() + Index + 1);
			RecvBuffer.erase(0, Index + 1);

			Contents.push_back(Content);
		}
	}

	else if (Result == 0)
	{
		std::cout << "Remote socket has closed." << std::endl;
		bAvailable = false; // ? Maybe local socket can reconnect to the remote
		return false;
	}

	else if (Result == SOCKET_ERROR)
	{
		std::cout << "Receiving failed with: " << WSAGetLastError() << std::endl;

		// These errors will not cause socket closing.
		// Next tick will try to send again.
		if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
			return false;

		std::cout << "Terrible error" << std::endl;
		// However other errors will cause the socket closing.
		bAvailable = false;
		closesocket(SocketFD);
		return false;
	}

	//std::cout << "The entire content: " << std::endl<< Contents << std::endl;
	return true;
}

void ULocalSocket::Init(WinSocket LocalSocketFD, const WinSocketAddrIn& LocalAddr)
{
	SocketFD = LocalSocketFD;
	AddrIn = LocalAddr;
	bAvailable = true;

	unsigned long ul = 1;
	int ret = ioctlsocket(SocketFD, FIONBIO, (unsigned long*)& ul);
}

void ULocalSocket::Init()
{
}

void ULocalSocket::Tick(float DeltaTime)
{
	_Send();
	_Receive();
}

std::string ULocalSocket::GetAddress()
{
	const size_t IPv4Len = 50;
	char* IPv4Ptr = new char[IPv4Len];
	inet_ntop(AF_INET, &AddrIn.sin_addr, IPv4Ptr, IPv4Len);

	return "LocalAddr : " + std::string(IPv4Ptr) + ":" + std::to_string(AddrIn.sin_port);
}

void ULocalSocket::SetSocket()
{
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	// recvfrom time out
	setsockopt(SocketFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)& tv, sizeof tv);
	// sendto time out
	setsockopt(SocketFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)& tv, sizeof tv);
}

bool ULocalSocket::IsValid()
{
	return bAvailable;
}

void ULocalSocket::Send(std::shared_ptr<std::string> MessagePtr)
{
	if (MessagePtr->size() > SO_SNDBUF) {
		
		std::cout << "The message is too big" << std::endl;
		return;
	}

	Out.push_back(MessagePtr);
}

std::shared_ptr<std::string> ULocalSocket::Receive()
{
	if (In.size() < 1) return nullptr;
	
	std::shared_ptr<std::string> MessagePtr = *(In.begin());
	
	if (MessagePtr.get() != nullptr)
	{
		In.erase(In.begin());
		return MessagePtr;
	}
	else {
		return nullptr;
	}
}
