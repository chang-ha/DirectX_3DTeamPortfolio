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
	// CP_ACP �ü���� ����ϴ°Ŵ�
	// �ƹ��͵� ���� ������ => _Text.c_str()�� �����Ʈ�� �Ǿ�� widechar�� ��ȯ�Ҽ� �ִ����� �������ݴϴ�.
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
	// CP_ACP �ü���� ����ϴ°Ŵ�
// �ƹ��͵� ���� ������ => _Text.c_str()�� �����Ʈ�� �Ǿ�� widechar�� ��ȯ�Ҽ� �ִ����� �������ݴϴ�.
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
	// CP_ACP �ü���� ����ϴ°Ŵ�
// �ƹ��͵� ���� ������ => _Text.c_str()�� �����Ʈ�� �Ǿ�� widechar�� ��ȯ�Ҽ� �ִ����� �������ݴϴ�.
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�Ҽ��� �����ϴ�.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�� �����߽��ϴ�.");
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
		nullptr, // �̺κ��� nullptr�� �־��ָ� ��ȯ �Լ��� �����ϴ°� �ƴϰ�. ��ȯ���̸� üũ�ϴ� �Լ��� �����Ѵ�.
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