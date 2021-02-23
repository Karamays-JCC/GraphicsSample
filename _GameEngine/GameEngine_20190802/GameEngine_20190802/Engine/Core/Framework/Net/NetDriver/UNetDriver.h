#pragma once
#include <Global/Global.h>

class UNetConnection;
class UChannel;

class UNetDriver
{
public:
	UNetDriver();
	virtual ~UNetDriver();

private:
	std::shared_ptr<UNetConnection> ServerConnection;

	std::vector<std::shared_ptr<UNetConnection>> ClientConnections;

	std::unordered_map<std::string, std::shared_ptr<UNetConnection>> MappedClientConnections;

	/** List of channels that were previously used and can be used again */
	std::vector<std::shared_ptr<UChannel>> ActorChannelPool;

public:

	virtual int ServerReplicateActors(float DeltaSeconds);

};

