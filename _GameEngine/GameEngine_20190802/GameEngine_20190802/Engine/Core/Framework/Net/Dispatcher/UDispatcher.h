#pragma once
#include <Global/Global.h>

class UDispatcher
{
public:
	UDispatcher();
	virtual ~UDispatcher();

public:
	void Init();

	void PublishTask(std::shared_ptr<class UNetPackage> Package);

private:
	void ClientUpdate(const std::string& Content);

	void ClientLogin(const std::string& Content);

};

