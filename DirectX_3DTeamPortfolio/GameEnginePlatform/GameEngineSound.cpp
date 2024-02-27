#include "PreCompile.h"
#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// lib�� ������ ����ϰڴٴ� ��ó�����Դϴ�.
// lib�� �����̴�.
#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

////////////////////////////////////////////////// SoundPlayer

void GameEngineSoundPlayer::SetLoop(int _Count)
{
	Control->setLoopCount(_Count);
}

void GameEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * GameEngineSound::GlobalVolume);
}

void GameEngineSoundPlayer::Stop()
{
	Control->stop();
}

void GameEngineSoundPlayer::Pause()
{
	Control->setPaused(true);
}

void GameEngineSoundPlayer::Resume()
{
	Control->setPaused(false);
}

bool GameEngineSoundPlayer::IsPlaying()
{
	bool Result = false;
	if (FMOD_OK != Control->isPlaying(&Result))
	{
		return false;
	}
	return Result;
}

std::string GameEngineSoundPlayer::GetCurSoundName()
{
	FMOD::Sound* _Sound;
	if (FMOD_OK != Control->getCurrentSound(&_Sound))
	{
		MsgBoxAssert("FMOD::Sound�� �����µ� �����߽��ϴ�.");
	}

	char _Name[512] = {};
	if (FMOD_OK != _Sound->getName(_Name, 512))
	{
		MsgBoxAssert("�̸��� �����µ� �����߽��ϴ�.");
	}
	std::string Result = _Name;

	return Result;
}

//////////////////////////////////////////////// ������ ���� �ڵ� 

// FMOD�� ����ϱ� ���� �ڵ� �� ��ü
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		// �̷� �ܺ� �Լ��� ���ο��� new�� �ϰ� �ֽ��ϴ�.
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
		}
		
		// 3D Setting
		// dopplerscale -> ��������ų� �־����� ��ġ�� �ö󰡰� ������
		// distancefactor -> ���÷������� ������ ��ħ
		// rolloffscale -> ����ȿ�� ����
		if (FMOD_RESULT::FMOD_OK != SoundSystem->set3DSettings(1.f, 1.f, .5f))
		{
			MsgBoxAssert("3D ���� ���ÿ� �����߽��ϴ�.");
		}
	}

	~SoundSystemCreator()
	{


		SoundSystem->release();
	}
};


void GameEngineSound::Update()
{
	if (nullptr == SoundSystem)
	{
		MsgBoxAssert("Sound System�� �������� �ʾƼ� ���� ������Ʈ�� �������� �����ϴ�.");
	}

	SoundSystem->update();
}



SoundSystemCreator SoundInitObject = SoundSystemCreator();
float GameEngineSound::GlobalVolume = 1.0f;
FMOD_VECTOR GameEngineSound::Vel = { 0.f, 0.f, 0.f };

std::map<std::string, std::shared_ptr<GameEngineSound>> GameEngineSound::AllSound;
std::map<std::string, std::shared_ptr<GameEngineSound>> GameEngineSound::All3DSound;


GameEngineSound::GameEngineSound() 
{
}

GameEngineSound::~GameEngineSound() 
{
	if (nullptr != SoundHandle)
	{
		SoundHandle->release();
	}
}

//
//void GameEngineSound::Init()
//{
//	static bool IsOnce = false;
//
//	if (true == IsOnce)
//	{
//		return;
//	}
//
//
//
//
//	// Fmod�� ����ϱ� ���� �غ� �ϴ� �Լ�
//	IsOnce = true;
//}

std::shared_ptr<GameEngineSound> GameEngineSound::FindSound(std::string_view _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, std::shared_ptr<GameEngineSound>>::iterator FindIter = AllSound.find(UpperName);

	if (FindIter == AllSound.end())
	{
		return nullptr;
	}
	
	return FindIter->second;
}

void GameEngineSound::SoundLoad(std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::shared_ptr<GameEngineSound> NewSound = std::make_shared<GameEngineSound>();

	NewSound->Load(_Path);

	AllSound.insert(std::make_pair(UpperName, NewSound));
}

GameEngineSoundPlayer GameEngineSound::SoundPlay(std::string_view _Name, int _Loop)
{
	std::shared_ptr<GameEngineSound> FindSoundPtr = FindSound(_Name);

	if (nullptr == FindSoundPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineSoundPlayer Player = FindSoundPtr->Play();

	Player.SetVolume(1.0f);

	Player.SetLoop(_Loop);

	return Player;
}

std::shared_ptr<GameEngineSound> GameEngineSound::Find3DSound(std::string_view _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, std::shared_ptr<GameEngineSound>>::iterator FindIter = All3DSound.find(UpperName);

	if (FindIter == All3DSound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::Sound3DLoad(std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::shared_ptr<GameEngineSound> NewSound = std::make_shared<GameEngineSound>();

	NewSound->Load3D(_Path);

	All3DSound.insert(std::make_pair(UpperName, NewSound));
}

GameEngineSoundPlayer GameEngineSound::Sound3DPlay(std::string_view _Name, const float4& _Pos, float _Volume /*= 1.0f*/, int _Loop/* = 0*/)
{
	std::shared_ptr<GameEngineSound> FindSoundPtr = Find3DSound(_Name);

	if (nullptr == FindSoundPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineSoundPlayer Player = FindSoundPtr->Play3D(_Pos);

	Player.SetVolume(_Volume);

	Player.SetLoop(_Loop);

	return Player;
}

void GameEngineSound::SetListenerPos(const float4& _Pos, const float4& _ForWard, const float4& _Up)
{
	static FMOD_VECTOR PrevPos = { 0.0f, 0.0f, 0.0f };

	FMOD_VECTOR Pos = { _Pos.X, _Pos.Y , _Pos.Z };

	//{
	//	Vel.x = (Pos.x - PrevPos.x) * (1000 / 60.f);
	//	Vel.y = (Pos.y - PrevPos.y) * (1000 / 60.f);
	//	Vel.z = (Pos.z - PrevPos.z) * (1000 / 60.f);
	//	PrevPos = Pos;
	//}

	// ForWard�� Up���ʹ� �����̾����
	float4 nForWard = _ForWard.NormalizeReturn();
	float4 nUp = _Up.NormalizeReturn();

	if (DirectX::XMVector3Equal(nUp.DirectXVector, DirectX::XMVector3Orthogonal(nForWard.DirectXVector)))
	{
		MsgBoxAssert("ForWard���Ϳ� Up���ʹ� �������迩�� �մϴ�.");
	}

	const FMOD_VECTOR ForWard = { nForWard.X, nForWard.Y , nForWard.Z };
	const FMOD_VECTOR Up = { nUp.X, nUp.Y , nUp.Z };

	SoundSystem->set3DListenerAttributes(0, &Pos , &Vel, &ForWard, &Up);
}

void GameEngineSound::Release()
{
	GameEngineSound::AllSound.clear();
	GameEngineSound::All3DSound.clear();
}



/////////////////////////////// �ɹ�




void GameEngineSound::Load(std::string_view _Path)
{
	// ��Ƽ����Ʈ => UTF-8 ���ڵ����� ��ȯ���� �Լ��� �ʿ��ϴ�.



	// "asdfasdfasdfad" <== ��Ƽ����Ʈ ���ڵ�
	// �̳༮�� ���ϴ� ���ڵ������ UTF-8
	// �ٷ����� �� �������� ������ ����ų ������ �ִ� string ���ڵ��� �Ⱦ����� �ϴ� �߼���.

	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);

	// const�� �Ⱥپ�������
	// �ε��� ������ ������ �������ִ� �ɼ� 
	SoundSystem->createSound(UTF8.c_str(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("���� �ε忡 �����߽��ϴ�.");
	}
}

void GameEngineSound::Load3D(std::string_view _Path)
{
	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);

	FMOD_MODE Mode = FMOD_3D | FMOD_LOOP_NORMAL;
	FMOD_RESULT Result = SoundSystem->createSound(UTF8.c_str(), Mode, 0, &SoundHandle);
	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("���� �ε忡 �����߽��ϴ�.");
	}
}


FMOD::Channel* GameEngineSound::Play()
{
	FMOD::Channel* SoundControl = nullptr;

 	SoundSystem->playSound(SoundHandle, nullptr, false, &SoundControl);
	return SoundControl;
}

FMOD::Channel* GameEngineSound::Play3D(const float4& _Pos, float _MinDistance, float _MaxDistance)
{
	FMOD::Channel* SoundControl = nullptr;
	
	FMOD_VECTOR Pos = { _Pos.X, _Pos.Y, _Pos.Z };
	FMOD_VECTOR vel = { 0.f, 0.f, 0.f };

	FMOD_RESULT Result;
	
	Result = SoundSystem->playSound(SoundHandle, 0, true, &SoundControl);

	Result = SoundControl->setMode(FMOD_3D_LINEARSQUAREROLLOFF);
	Result = SoundControl->set3DAttributes(&Pos, &vel);
	Result = SoundControl->setPaused(false);

	SoundControl->set3DMinMaxDistance(_MinDistance, _MaxDistance);

	return SoundControl;
}
