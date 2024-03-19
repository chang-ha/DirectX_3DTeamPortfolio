#include "PreCompile.h"
#include "GlobalValue.h"
#include "ContentsCore.h"

GlobalValue::GlobalValue()
{

}

GlobalValue::~GlobalValue()
{

}

float4 GlobalValue::GetWinScale()
{
	return GameEngineCore::MainWindow.GetScale();
}