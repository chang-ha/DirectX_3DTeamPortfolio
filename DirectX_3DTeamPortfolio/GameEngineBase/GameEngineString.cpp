#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"


GameEngineString::GameEngineString() 
{
}

GameEngineString::~GameEngineString() 
{
}

// "" => L""

std::wstring GameEngineString::AnsiToUnicode(std::string_view _Text)
{
	// CP_ACP 운영체제가 사용하는거니
	// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		return L"";
	}

	// _Text 10
	// Size 30

	std::wstring Result;
	Result.resize(Size);


	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		return L"";
	}

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring_view& _Text)
{
	// CP_ACP 운영체제가 사용하는거니
// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		return "";
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring_view& _Text)
{
	// CP_ACP 운영체제가 사용하는거니
// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환할수가 없습니다.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환에 실패했습니다.");
		return "";
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(std::string_view _Text)
{
	std::wstring UniCode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(UniCode);
}


std::wstring GameEngineString::UTF8ToUnicode(const std::string_view& _Text)
{
	std::wstring UniCode;

	int32_t Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_Text.data(),
		static_cast<int32_t>(_Text.size()),
		nullptr, // 이부분을 nullptr로 넣어주면 변환 함수로 동작하는게 아니고. 변환길이를 체크하는 함수로 동작한다.
		0
	);

	if (0 >= Len)
	{
		GameEngineDebug::GetWindowLastErrorPrint();
		return L"";
	}

	UniCode.resize(Len);

	Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_Text.data(),
		static_cast<int32_t>(_Text.size()),
		&UniCode[0],
		Len
	);

	if (0 >= Len)
	{
		GameEngineDebug::GetWindowLastErrorPrint();
		return L"";
	}

	return UniCode;
}

std::string GameEngineString::UTF8ToAnsi(std::string_view _Text)
{
	std::wstring UniCode = UTF8ToUnicode(_Text);
	std::string Return = UnicodeToAnsi(UniCode);
	return Return;
}