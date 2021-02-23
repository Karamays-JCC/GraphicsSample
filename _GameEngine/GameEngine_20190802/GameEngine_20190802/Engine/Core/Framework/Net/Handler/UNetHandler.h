#pragma once
#include <Global/Global.h>

class UNetHandler
{
public:
	UNetHandler();
	virtual ~UNetHandler();

public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

};

