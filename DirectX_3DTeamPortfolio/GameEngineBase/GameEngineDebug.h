#pragma once
#include <string>
#include <assert.h>

//// ���� :
namespace GameEngineDebug
{
	void LeakCheck();
	void GetWindowLastErrorPrint();
};

#define MsgBoxAssert(Text) \
std::string Value = Text; \
MessageBoxA(nullptr, Value.c_str(), "Error", MB_OK); assert(false);
