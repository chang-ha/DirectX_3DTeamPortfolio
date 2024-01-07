#pragma once
#include "GameEngineGUI.h"
#include "GAMEENGINERENDERTARGET.H"
#include <GameEngineBase/GameEngineThreadJobQueue.h>
#include <GameEngineBase/GameEngineNetServer.h>
#include <GameEngineBase/GameEngineNetClient.h>

enum class NetType 
{
	None,
	Server,
	Client,
};

class GameEngineNetWindow : public GameEngineGUIWindow
{
	static GameEngineNet* Net;

public:
	// constrcuter destructer
	GameEngineNetWindow();
	~GameEngineNetWindow();

	// delete Function
	GameEngineNetWindow(const GameEngineNetWindow& _Other) = delete;
	GameEngineNetWindow(GameEngineNetWindow&& _Other) noexcept = delete;
	GameEngineNetWindow& operator=(const GameEngineNetWindow& _Other) = delete;
	GameEngineNetWindow& operator=(GameEngineNetWindow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;

private:
	char IPBuffer[100] = "127.0.0.1";

	NetType NetTypeValue = NetType::None;

	GameEngineNetServer Server;
	GameEngineNetClient Client;
};

