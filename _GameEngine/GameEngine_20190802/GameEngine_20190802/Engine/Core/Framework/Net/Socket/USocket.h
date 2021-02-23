#pragma once

#include <Global/Global.h>
class USocket
{
public:
	USocket();
	virtual ~USocket();

public:
	virtual std::string GetAddress();

};

