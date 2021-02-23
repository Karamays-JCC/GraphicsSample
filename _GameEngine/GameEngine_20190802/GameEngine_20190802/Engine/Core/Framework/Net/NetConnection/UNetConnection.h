#pragma once
#include <Global/Global.h>
#include <Framework/Net/Player/UPlayer.h>
#include <Framework/Net/Socket/RemoteSocket/URemoteSocket.h>
#include <Framework/Net/Socket/LocalSocket/ULocalSocket.h>

class UChannel;
class UActorChannel;
class UNetDriver;
class AActor;

enum EConnectionState
{
	USOCK_Invalid = 0, // Connection is invalid, possibly uninitialized.
	USOCK_Closed = 1, // Connection permanently closed.
	USOCK_Pending = 2, // Connection is awaiting connection.
	USOCK_Open = 3, // Connection is open.
};

namespace ESecurityEvent
{
	enum Type
	{
		Malformed_Packet = 0, // The packet didn't follow protocol
		Invalid_Data = 1,     // The packet contained invalid data
		Closed = 2            // The connection had issues (potentially malicious) and was closed
	};

	/** @return the stringified version of the enum passed in */
	inline const TCHAR* ToString(const ESecurityEvent::Type EnumVal)
	{
		switch (EnumVal)
		{
		case Malformed_Packet:
		{
			return TEXT("Malformed_Packet");
		}
		case Invalid_Data:
		{
			return TEXT("Invalid_Data");
		}
		case Closed:
		{
			return TEXT("Closed");
		}
		}
		return TEXT("");
	}
}

/** If this connection is from a client, this is the current login state of this connection/login attempt */
namespace EClientLoginState
{
	enum Type
	{
		Invalid = 0,		// This must be a client (which doesn't use this state) or uninitialized.
		LoggingIn = 1,		// The client is currently logging in.
		Welcomed = 2,		// Told client to load map and will respond with SendJoin
		ReceivedJoin = 3,		// NMT_Join received and a player controller has been created
		CleanedUp = 4			// Cleanup has been called at least once, the connection is considered abandoned/terminated/gone
	};

	/** @return the stringified version of the enum passed in */
	inline const TCHAR* ToString(const EClientLoginState::Type EnumVal)
	{
		switch (EnumVal)
		{
		case Invalid:
		{
			return TEXT("Invalid");
		}
		case LoggingIn:
		{
			return TEXT("LoggingIn");
		}
		case Welcomed:
		{
			return TEXT("Welcomed");
		}
		case ReceivedJoin:
		{
			return TEXT("ReceivedJoin");
		}
		case CleanedUp:
		{
			return TEXT("CleanedUp");
		}
		}
		return TEXT("");
	}
};


class UNetConnection : 
	public UPlayer
{
public:
	UNetConnection();
	virtual ~UNetConnection();

private:
	/**  child connections for secondary viewports */
	std::vector<std::shared_ptr<class UChildConnection>> Children;

	/** Owning net driver */
	std::shared_ptr<class UNetDriver> Driver;
	
	/** @todo document Control, Actor, Voice Channels */
	std::vector<std::shared_ptr<class UChannel>> OpenChannels;

	/** Reference to controlling actor (usually PlayerController) */
	std::shared_ptr<class AActor> OwningActor;


	std::vector<std::shared_ptr<class UNetPackage>> In;

	std::vector<std::shared_ptr<class UNetPackage>> Out;
	
private:
	void _Send();

	void _Receive();

public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

public:
	ULocalSocket Local;

	URemoteSocket Remote;

public:
	void Send(std::shared_ptr<class UNetPackage> OutPackage);

	std::shared_ptr<class UNetPackage> Receive();

	void CreateConnection(SOCKET LocalSocketFD, const sockaddr_in& LocalAddr, const sockaddr_in& RemoteAddr);

	bool IsValid();

};

