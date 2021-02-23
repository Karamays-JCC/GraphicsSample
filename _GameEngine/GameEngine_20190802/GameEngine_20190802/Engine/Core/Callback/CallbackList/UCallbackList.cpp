#include "UCallbackList.h"

UCallbackList::UCallbackList()
{
	Init();
}

UCallbackList::~UCallbackList()
{
}

void UCallbackList::Init()
{
	AxisMappings.emplace(EKey::Key_W, std::make_pair("MoveForward", -1));
	AxisMappings.emplace(EKey::Key_A, std::make_pair("MoveRight", -1));
	AxisMappings.emplace(EKey::Key_S, std::make_pair("MoveForward", 1));
	AxisMappings.emplace(EKey::Key_D, std::make_pair("MoveRight", 1));
	AxisMappings.emplace(EKey::Key_Space, std::make_pair("MoveUp", 1));
	AxisMappings.emplace(EKey::Key_X, std::make_pair("MoveUp", -1));


	//ActionMappings.emplace(EKey::Key_Space, "Jump");

}

void UCallbackList::NotifyAxisFunc(const EKey Key, float DeltaTime)
{

	auto Itm = AxisMappings.find(Key);
	if (Itm != AxisMappings.cend())
	{
		const std::string AxisName = Itm->second.first;
		const float Scale = Itm->second.second;
		const float Value = DeltaTime * Scale;

		auto Itl = AxisCallbackList.find(AxisName);
		if (Itl != AxisCallbackList.cend())
		{
			Itl->second(Value);
		}
	}
	
}

void UCallbackList::NotifyActionFunc(const EKey Key, EInputEvent KeyEvent)
{
	
	auto Itm = ActionMappings.find(Key);
	if (Itm != ActionMappings.cend())
	{
		std::string ActionName = Itm->second;
		switch (KeyEvent)
		{
		case IE_Pressed:
		{
			auto It = ActionPressedCallbackList.find(ActionName);
			if (It != ActionPressedCallbackList.cend())
			{
				It->second();
			}
		}
			break;
		case IE_Released:
		{
			auto It = ActionReleasedCallbackList.find(ActionName);
			if (It != ActionReleasedCallbackList.cend())
			{
				It->second();
			}
		}
			break;
		case IE_Repeat:
			break;
		case IE_DoubleClick:
			break;
		case IE_Axis:
			break;
		case IE_MAX:
			break;
		default:
			break;
		}
	}
}
