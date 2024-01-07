#pragma once

// Ό³Έν :
class GameServer
{
public:
	// constructer destructer
	GameServer();
	~GameServer();

	// delete Function
	GameServer(const GameServer& _Other) = delete;
	GameServer(GameServer&& _Other) noexcept = delete;
	GameServer& operator = (const GameServer& _Other) = delete;
	GameServer& operator = (GameServer&& _Other) noexcept = delete;

protected:

private:

};

