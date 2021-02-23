#include "UClient.h"
#include <Framework/Net/NetConnection/UNetConnection.h>
#include <Framework/Net/NetPackage/UNetPackage.h>

UClient::UClient()
{
	x = 0;
	y = 0;
	z = 0;
	MainNetConnection = std::make_shared<class UNetConnection>();
}

UClient::~UClient()
{
}

void UClient::_Send()
{
	for (auto It = Out.begin(); It != Out.end(); ++It)
	{
		MainNetConnection->Send(*It);
	}
	Out.clear();
}

void UClient::_Receive()
{
	In.push_back(MainNetConnection->Receive());
}

void UClient::Init()
{
	int iRet = 0;
	iRet = WSAStartup(MAKEWORD(2, 2), &_WSAData);
	
	if (iRet != 0)
		std::cout << "execute failed" << std::endl;

	if (LOBYTE(_WSAData.wVersion) != 2 || HIBYTE(_WSAData.wVersion) != 2)
	{
		WSACleanup();
		std::cout << "version is not correct" << std::endl;
	}

	Connect();
}

void UClient::Tick(float DeltaTime)
{
	Sleep(1500);
	std::shared_ptr<UNetPackage> NewPackage = std::make_shared<UNetPackage>();
	NewPackage->Command = ECommand::Type::ClientUpdate;
	
	nlohmann::json tempJson /*= R"({"compact": true, "schema": 0})"_json*/;
	tempJson["x"] = x;
	tempJson["y"] = y;
	tempJson["z"] = z;
	NewPackage->Content = tempJson.dump();
	Send(NewPackage);
	
	_Send();
	_Receive();

	MainNetConnection->Tick(DeltaTime);

	x++;
	y++;
}


void UClient::Connect(std::string IP, unsigned int Port)
{
	/*
	std::string Pattern = "";
	std::regex IPChecker(Pattern);
	std::string IPString;

	while (!std::regex_match(IPString, IPChecker)) {
		std::cout << "Please enter the avaliable server IP :";
		std::cin >> IPString;
	}
	std::cout << "Format correct. Try to connect to the server ..." << std::endl;
	*/
	

	SOCKET LocalSocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == LocalSocketFD) {
		printf("[Client]: socker failed\n");
		WSACleanup();
		return;
	}

	sockaddr_in RemoteAddr;
	sockaddr_in LocalAddr;
	RemoteAddr.sin_family = AF_INET; // IPV4 group
	RemoteAddr.sin_addr.S_un.S_addr = inet_addr(IP.c_str()); // Remote(Server) IP
	RemoteAddr.sin_port = htons((short)Port); // Remote(Server) port
	int AddrLen = sizeof(sockaddr_in);

	int AttemptTimes = 3;
	std::cout << "[Client]: Try to connect to server ..." << std::endl;
	while (AttemptTimes > 0)
	{
		std::cout << "[Client]: " << AttemptTimes << " times remaining." << std::endl;
		int Result = connect(LocalSocketFD, (LPSOCKADDR)& RemoteAddr, AddrLen);
		
		if (Result == 0) {
			getsockname(LocalSocketFD, (LPSOCKADDR)& LocalAddr, &AddrLen);
			break; //SOCKET_ERROR£¨-1£©
		}

		printf("[Client]: Trying failed.\n");
		printf("[Client]: error code %d \n", WSAGetLastError());
		AttemptTimes--;

		if (AttemptTimes == 0 && Result != 0)
		{
			closesocket(LocalSocketFD);
			WSACleanup();
			return;
		}
	}

	std::cout << "[Client]: This PC has connected to target server." << std::endl;
	// if connecting success, create the connection entity.
	MainNetConnection->CreateConnection(LocalSocketFD, LocalAddr, RemoteAddr);
}

void UClient::Send(std::shared_ptr<class UNetPackage> OutPackage)
{
	Out.push_back(OutPackage);
}

std::shared_ptr<class UNetPackage> UClient::Recive()
{
	if (In.size() < 1) return nullptr;

	auto PackagePtr = std::make_shared<UNetPackage>();
	PackagePtr = *(In.begin());

	In.erase(In.begin());

	return PackagePtr;
}


