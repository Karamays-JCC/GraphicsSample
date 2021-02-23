#pragma once
#include <functional>

template<typename ParamTy1, typename ParamTy2>
struct LessComp_01 : public std::binary_function<ParamTy1, ParamTy2, bool>
{
	bool operator()(ParamTy1 Param1, ParamTy2 Param2)
	{
		// 编译期 的情况非常值得玩味
		return Param1 < Param2;
	}
};

