#pragma once
#include <Global/Global.h>
class UListeningSocket
{
public:
	UListeningSocket();

	virtual ~UListeningSocket();

public:
	void Init(unsigned int _MaxQueueNum);

	void Bind(unsigned int _Port);

	void Listen();

private:
	SOCKET FD;

	SOCKADDR_IN InternetAddress;

	unsigned int MaxQueueNum;

	unsigned int Port;

public:
	FORCEINLINE SOCKET GetFD() const { return FD; };
};

