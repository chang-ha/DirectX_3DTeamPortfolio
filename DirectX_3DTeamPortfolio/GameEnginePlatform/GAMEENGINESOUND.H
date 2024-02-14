#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// 선언
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

class GameEngineSoundPlayer 
{
	friend class GameEngineSound;

public:
	void SetLoop(int _Count);
	void SetVolume(float _Volume);
	void Stop();
	void Pause();
	void Resume();
	bool IsPlaying();
	std::string GetCurSoundName();

	GameEngineSoundPlayer() 
	{

	}


private:
	GameEngineSoundPlayer(FMOD::Channel* _Control)
		: Control(_Control)
	{
	}

	FMOD::Channel* Control = nullptr;
};

// 설명 :
class GameEngineSound
{
	static float GlobalVolume;

	// Management

	friend class SoundSystemCreator;
	friend class GameEngineSoundPlayer;

private:
	static std::map<std::string, std::shared_ptr<GameEngineSound>> AllSound;
	static std::map<std::string, std::shared_ptr<GameEngineSound>> All3DSound;

public:
	static void SetGlobalVolume(float _Value) 
	{
		GlobalVolume = _Value;
	}

	static float GetGlobalVolume()
	{
		return GlobalVolume;
	}

	// 2D
	static void SoundLoad(std::string_view _Path)
	{
		GameEnginePath Path = GameEnginePath(_Path);
		SoundLoad(Path.GetFileName(), _Path);
	}

	static std::shared_ptr<GameEngineSound> FindSound(std::string_view _Name);

	static void SoundLoad(std::string_view _Name, std::string_view _Path);

	static GameEngineSoundPlayer SoundPlay(std::string_view _Name, int _Loop = 0);

	// 3D
	static void Sound3DLoad(std::string_view _Path)
	{
		GameEnginePath Path = GameEnginePath(_Path);
		Sound3DLoad(Path.GetFileName(), _Path);
	}

	static std::shared_ptr<GameEngineSound> Find3DSound(std::string_view _Name);

	static void Sound3DLoad(std::string_view _Name, std::string_view _Path);

	static GameEngineSoundPlayer Sound3DPlay(std::string_view _Name, const float4& _Pos, float _Volume = 1.0f, int _Loop = 0);

	static void SetListenerPos(const float4& _Pos, const float4& _ForWard, const float4& _Up);

	static void SetVel(const float4& _Vel)
	{
		Vel.x = _Vel.X;
		Vel.y = _Vel.Y;
		Vel.z = _Vel.Z;
	}

	static void Release();

	static void Update();

public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:

	// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
	// GameEngineSound::SoundPlay("AAA.Mp3");
	// GameEngineSound::PlayBgm("AAA.Mp3");
	// GameEngineSound::StopBgm("AAA.Mp3");
private:
	FMOD::Sound* SoundHandle = nullptr;

	void Load(std::string_view _Path);
	void Load3D(std::string_view _Path);

	FMOD::Channel* Play();


	// 공간속에서 초당 소리의 속도
	// 추후 조정기능 필요시 구현
	static FMOD_VECTOR Vel;

	FMOD::Channel* Play3D(const float4& _Pos);
};

