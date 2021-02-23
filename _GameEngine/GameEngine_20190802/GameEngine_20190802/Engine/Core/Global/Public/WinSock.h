#pragma once

#include <WinSock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

enum class EOptionSO : int
{
	// Option flags per-socket.
	Debug = SO_DEBUG,
	AcceptConn = SO_ACCEPTCONN,
	ReuseAddr = SO_REUSEADDR,
	KeepAlive = SO_KEEPALIVE,
	DontRoute = SO_DONTROUTE,
	Broadcast = SO_BROADCAST,
	UseLoopBack = SO_USELOOPBACK,
	Linger = SO_LINGER,
	OOBInLine = SO_OOBINLINE,

	DontLinger = SO_DONTLINGER,
	ExclusiveAddrUse = SO_EXCLUSIVEADDRUSE,

	// Additional options
	SendBufferSize = SO_SNDBUF,
	ReciveBufferSize = SO_RCVBUF,
	SendLowWaterMark = SO_SNDLOWAT,
	ReciveLowWaterMark = SO_RCVLOWAT,
	SendTimeout = SO_SNDTIMEO,
	ReciveTimeout = SO_RCVTIMEO,
	Error = SO_ERROR,
	Type = SO_TYPE,

	// WindSock 2 extension -- new options
	GroupId = SO_GROUP_ID,
	GroupPriority = SO_GROUP_PRIORITY,
	MaxMessageSize = SO_MAX_MSG_SIZE,
	ProtocolInfo = SO_PROTOCOL_INFO,
	ProviderConfigInfo = PVD_CONFIG,
	ConditionalAccept = SO_CONDITIONAL_ACCEPT

};