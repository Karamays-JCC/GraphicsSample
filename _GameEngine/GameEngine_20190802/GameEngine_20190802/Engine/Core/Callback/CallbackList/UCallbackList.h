#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

enum class EKey : unsigned int {
	Key_Q,
	Key_W,
	Key_A,
	Key_S,
	Key_D,
	Key_E,
	Key_X,
	Key_Escape,
	Key_Space
};

enum EInputEvent
{
	IE_Pressed = 0,
	IE_Released = 1,
	IE_Repeat = 2,
	IE_DoubleClick = 3,
	IE_Axis = 4,
	IE_MAX = 5,
};

struct EventList
{
	using AxisFunc = std::function<void(float)>;
	using ActionFunc = std::function<void()>;

};

class UCallbackList
{
	using AxisFunc = EventList::AxisFunc;
	using ActionFunc = EventList::ActionFunc;

public:
	UCallbackList();
	virtual ~UCallbackList();

public:
	void Init();
	void NotifyAxisFunc(const EKey Key, float DeltaTime);
	void NotifyActionFunc(const EKey Key, EInputEvent KeyEvent);

public:
	template<class UserClass, class FunctionPtr>
	void BindAxis(const std::string& AxisName, UserClass* Object, FunctionPtr Func);
	template<class UserClass, class FunctionPtr>
	void BindAction(const std::string& ActionName, EInputEvent KeyEvent, UserClass* Object, FunctionPtr Func);

private:
	std::unordered_map<EKey, std::pair<std::string, float>> AxisMappings;
	std::unordered_map<std::string, AxisFunc> AxisCallbackList;

	std::unordered_map<EKey, std::string> ActionMappings;
	std::unordered_map<std::string, ActionFunc> ActionPressedCallbackList;
	std::unordered_map<std::string, ActionFunc> ActionReleasedCallbackList;

};

template<class UserClass, class FunctionPtr>
inline void UCallbackList::BindAxis(const std::string& AxisName, UserClass* Object, FunctionPtr Func)
{
	AxisFunc AxisFunction = std::bind(Func, Object, std::placeholders::_1);
	AxisCallbackList.emplace(AxisName, std::move(AxisFunction));
}

template<class UserClass, class FunctionPtr>
inline void UCallbackList::BindAction(const std::string& ActionName, EInputEvent KeyEvent, UserClass* Object, FunctionPtr Func)
{
    ActionFunc ActionFunc = std::bind(Func, Object);
	switch (KeyEvent)
	{
	case IE_Pressed: 
	{
		ActionPressedCallbackList.emplace(ActionName, ActionFunc); 
		break;
	}
	case IE_Released: 
	{
		ActionReleasedCallbackList.emplace(ActionName, ActionFunc); 
		break;
	}
	default:
	{
		break;
	}
	}
}
