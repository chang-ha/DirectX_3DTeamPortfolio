#pragma once
#include "GameEngineLevel.h"
#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineNet.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// 설명 :
class GameEngineCore
{
	friend class GameEngineLevel;

public:
	static GameEngineTime MainTime;
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;


	// GameEngineCoreObject를 상속받은 클래스만 템플릿으로 사용 가능하다.
	template<typename ObjectType>
	static void EngineStart(HINSTANCE _Inst) 
	{
		CoreObject = std::make_shared<ObjectType>();
		EngineProcess(_Inst, ObjectType::GetWindowTitle(), ObjectType::GetStartWindowPos(), ObjectType::GetStartWindowSize());
	}


	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 이미 존재합니다.");
			return;
		}

		std::shared_ptr<GameEngineLevel> TempCurLevel = CurLevel;
		std::shared_ptr<GameEngineLevel> NewLevel = std::make_shared<LevelType>();
		CurLevel = NewLevel;
		LevelInit(NewLevel, _Name);
		CurLevel = TempCurLevel;
		AllLevel.insert(std::make_pair(Upper, NewLevel));
	}

	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, std::shared_ptr<GameEngineLevel>>::iterator Finditer = AllLevel.find(Upper);

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() == Finditer)
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 존재하지 않습니다.");
			return;
		}

		NextLevel = Finditer->second;
	}

	static std::shared_ptr<class GameEngineRenderTarget> GetBackBufferRenderTarget()
	{
		return MainDevice.GetBackBufferRenderTarget();
	}

	static ID3D11Device* GetDevice() 
	{
		return MainDevice.GetDevice();
	}

	static ID3D11DeviceContext* GetContext()
	{
		return MainDevice.GetContext();
	}

	static std::map<std::string, std::shared_ptr<GameEngineLevel>>& GetAllLevel() 
	{
		return AllLevel;
	}

	static std::shared_ptr<GameEngineLevel> GetCurLevel() 
	{
		return CurLevel;
	}

	static void SetNet(GameEngineNet* _Net)
	{
		Net = _Net;
	}

	static void SetLimitFrame(int _Frame)
	{
		LimitFrame = _Frame;
		PrevSleepTime = 0.f;
	}

protected:

private:
	static GameEngineNet* Net;
	static GameEngineDevice MainDevice;

	static void EngineProcess(HINSTANCE _Inst, const std::string& _Name, float4 _Pos, float4 _Size);
	static std::shared_ptr<GameEngineObject> CoreObject;

	static void LevelInit(std::shared_ptr<GameEngineLevel> _Level, std::string_view _Name);

	static std::shared_ptr<GameEngineLevel> CurLevel;
	static std::shared_ptr<GameEngineLevel> NextLevel;
	static std::map<std::string, std::shared_ptr<GameEngineLevel>> AllLevel;


	static void Start();
	static void Update();
	static void Release();

	static void Resources_Release();

	static int LimitFrame;
	static float PrevSleepTime;
	static void FrameLimit(float& _Delta);


};

