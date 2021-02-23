#pragma once
#include <Global/Global.h>
#include <Framework/Object/UObject.h>

enum EChannelType
{
	CHTYPE_None = 0,  // Invalid type.
	CHTYPE_Control = 1,  // Connection control.
	CHTYPE_Actor = 2,  // Actor-update channel.

	// @todo: Remove and reassign number to CHTYPE_Voice (breaks net compatibility)
	CHTYPE_File = 3,  // Binary file transfer.

	CHTYPE_Voice = 4,  // VoIP data channel
	CHTYPE_MAX = 8,  // Maximum.
};

class UChannel :
	public UObject
{
private:
	std::shared_ptr<class UNetConnection> Connection; // Owner Connection



};

