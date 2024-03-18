#pragma once

// ���� :
class LothricKn_Debug
{
public:
	// constrcuter destructer
	LothricKn_Debug();
	~LothricKn_Debug();

	// delete Function
	LothricKn_Debug(const LothricKn_Debug& _Other) = delete;
	LothricKn_Debug(LothricKn_Debug&& _Other) noexcept = delete;
	LothricKn_Debug& operator=(const LothricKn_Debug& _Other) = delete;
	LothricKn_Debug& operator=(LothricKn_Debug&& _Other) noexcept = delete;

	void OutPutChangeState(int _State, std::string_view _AniName);
	bool IsDebug() const;
	void DebugOn();
	void DebugOff();

protected:
	std::string GetDebugString(int _State);

private:
	int CurState = -1;

	bool IsDebugMode = false;

};

