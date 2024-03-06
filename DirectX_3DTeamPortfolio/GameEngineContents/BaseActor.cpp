#include "PreCompile.h"
#include "BaseActor.h"

#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"
#include "DummyPolyCollision.h"
#include "ContentsDebug.h"

#include "DS3DummyData.h"


class ContentsActorInitial
{
private:
	ContentsActorInitial()
	{
		Init();
	}

	~ContentsActorInitial() {}

	void Init();

private:
	static ContentsActorInitial s_ActorInit;

};

void ContentsActorInitial::Init()
{
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Wake, Enum_ActorFlagBit::Wake));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Death, Enum_ActorFlagBit::Death));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Parrying, Enum_ActorFlagBit::Parrying));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Guarding, Enum_ActorFlagBit::Guarding));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Hit, Enum_ActorFlagBit::Hit));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::HyperArmor, Enum_ActorFlagBit::HyperArmor));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Block_Shield, Enum_ActorFlagBit::Block_Shield));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Guard_Break, Enum_ActorFlagBit::Guard_Break));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::Break_Posture, Enum_ActorFlagBit::Break_Posture));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::TwoHand, Enum_ActorFlagBit::TwoHand));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::FrontStab, Enum_ActorFlagBit::FrontStab));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorFlag::BackStab, Enum_ActorFlagBit::BackStab));
}

std::unordered_map<Enum_ActorFlag, Enum_ActorFlagBit> BaseActor::FlagIndex;
ContentsActorInitial ContentsActorInitial::s_ActorInit;
BaseActor::BaseActor()
{
	mJumpTableManager.Owner = this;
}

BaseActor::~BaseActor()
{
}

void BaseActor::Start()
{
	MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	MainRenderer->Transform.SetLocalScale(float4(W_SCALE, W_SCALE, W_SCALE));

	Stat.SetPoise(100); // 모든 객체가 강인도 100을 가지고 있음 << DS3 Official
}

void BaseActor::Update(float _Delta)
{
	MainState.Update(_Delta);
	if (nullptr != Target && true == Target->IsDeath())
	{
		Target = nullptr;
	}
	CalcuTargetAngle();
	mJumpTableManager.Update();
}

void BaseActor::Release()
{
	MainRenderer = nullptr;
	SocketCollisions.clear();
	Target = nullptr;
	mJumpTableManager.Release();
}

void BaseActor::AddWDirection(float _Degree)
{
	Transform.AddWorldRotation(float4(0.0f, 0.0f, _Degree));
}

void BaseActor::SetWDirection(float _Degree)
{
	Transform.SetWorldRotation(float4(0.0f, 0.0f, _Degree));
}

float BaseActor::GetWDirection() const
{
	return Transform.GetWorldRotationEuler().Z;
}

void BaseActor::SetWPosition(const float4& _wPos)
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("피직스 액터를 사용하지 않고 사용할 수 없는 기능입니다.");
		return;
	}

	Capsule->SetWorldPosition(_wPos);
}

int BaseActor::FindFlag(Enum_ActorFlag _Status) const
{
	if (auto FindIter = FlagIndex.find(_Status); FindIter != FlagIndex.end())
	{
		return static_cast<int>(FindIter->second);
	}

	return static_cast<int>(Enum_ActorFlagBit::None);
}

bool BaseActor::IsFlag(Enum_ActorFlag _Flag) const
{
	return (Flags / FindFlag(_Flag)) % 2;
}

void BaseActor::SetFlag(Enum_ActorFlag _Flag, bool _Value)
{
	AddFlag(_Flag);

	if (false == _Value)
	{
		Flags -= FindFlag(_Flag);
	}
}

void BaseActor::AddFlag(Enum_ActorFlag _Flag)
{
	Flags |= FindFlag(_Flag);
}

void BaseActor::SubFlag(Enum_ActorFlag _Flag)
{
	SetFlag(_Flag, false);
}

void BaseActor::DebugFlag() const
{
	bool WakeValue = IsFlag(Enum_ActorFlag::Wake);
	bool DeathValue = IsFlag(Enum_ActorFlag::Death);
	bool ParryingValue = IsFlag(Enum_ActorFlag::Parrying);
	bool GuardingValue = IsFlag(Enum_ActorFlag::Guarding);
	bool HitValue = IsFlag(Enum_ActorFlag::Hit);
	bool HyperArmorValue = IsFlag(Enum_ActorFlag::HyperArmor);
	bool Block_ShieldValue = IsFlag(Enum_ActorFlag::Block_Shield);
	bool Guard_BreakValue = IsFlag(Enum_ActorFlag::Guard_Break);
	bool Break_PostureValue = IsFlag(Enum_ActorFlag::Break_Posture);
	bool TwoHandValue = IsFlag(Enum_ActorFlag::TwoHand);
	bool FrontStabValue = IsFlag(Enum_ActorFlag::FrontStab);
	bool BackStabValue = IsFlag(Enum_ActorFlag::BackStab);
	int a = 0;
}

float4x4& BaseActor::GetBoneMatrixToIndex(int _Index)
{
	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	return BoneMats[_Index];
}

std::shared_ptr<BoneSocketCollision> BaseActor::CreateSocketCollision(Enum_CollisionOrder _Order, int _SocketIndex, BSCol_TransitionParameter _Para, std::string_view _ColName)
{
	if (auto FindIter = SocketCollisions.find(_SocketIndex); FindIter != SocketCollisions.end())
	{
		MsgBoxAssert("이미 존재하는 충돌체를 생성하려 했습니다.");
		return nullptr;
	}

	std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Order);
	NewCol->SetName(_ColName);
	NewCol->SetBoneIndex(_SocketIndex);
	NewCol->SetCollisionType(ColType::SPHERE3D);
	NewCol->SetRendererTransformPointer(&MainRenderer->Transform);
	NewCol->SetSocket(&GetBoneMatrixToIndex(_SocketIndex));
	NewCol->SetAttachedMatrix(_Para.S, _Para.R, _Para.T);
	NewCol->Off();
	SocketCollisions.insert(std::make_pair(_SocketIndex, NewCol));
	return NewCol;
}

std::shared_ptr<DummyPolyCollision> BaseActor::CreateDummyPolyCollision(Enum_CollisionOrder _Order, const SetDPMatrixParameter& _Para, std::string _ColName /*= ""*/)
{
	std::shared_ptr<DummyPolyCollision> NewCol = CreateComponent<DummyPolyCollision>(_Order);
	NewCol->SetName(_ColName);
	NewCol->SetCollisionType(ColType::SPHERE3D);
	NewCol->SetRendererTransformPointer(&MainRenderer->Transform);
	int AttachBoneIndex = _Para.AttachBoneIndex;
	if (-1 != AttachBoneIndex)
	{
		NewCol->SetSocket(&GetBoneMatrixToIndex(_Para.AttachBoneIndex));
	}
	NewCol->SetDummyPolyMatrix(_Para);
	NewCol->Off();
	return NewCol;
}

std::shared_ptr<BoneSocketCollision> BaseActor::GetSocketCollision(int _Index)
{
	if (auto FindIter = SocketCollisions.find(_Index); FindIter != SocketCollisions.end())
	{
		return FindIter->second;
	}

	MsgBoxAssert("존재하지 않는 충돌체를 참조하려 했습니다.");
	return nullptr;
}

int BaseActor::GetSocketIndex(const std::shared_ptr<class BoneSocketCollision>& _pCol)
{
	for (const std::pair<const int, std::shared_ptr<BoneSocketCollision>>& Pair : SocketCollisions)
	{
		if (_pCol == Pair.second)
		{
			int Index = Pair.first;
			return Index;
		}
	}

	return -1;
}

void BaseActor::OnSocketCollision(int _BoneIndex)
{
	std::shared_ptr<BoneSocketCollision> pCollision = GetSocketCollision(_BoneIndex);
	if (nullptr == pCollision)
	{
		MsgBoxAssert("존재하지 않는 충돌체를 끄려고 했습니다.");
		return;
	}

	pCollision->On();
}

void BaseActor::OffSocketCollision(int _BoneIndex)
{
	std::shared_ptr<BoneSocketCollision> pCollision = GetSocketCollision(_BoneIndex);
	if (nullptr == pCollision)
	{
		MsgBoxAssert("존재하지 않는 충돌체를 끄려고 했습니다.");
		return;
	}

	pCollision->Off();
}

std::string_view BaseActor::GetFloorMaterialName()
{
	if (FloorMaterialSoundRes.empty())
	{
		MsgBoxAssert("존재하지 않는 자료를 반환하려했습니다.");
		static std::string ReturnValue;
		return ReturnValue;
	}

	int Size = static_cast<int>(FloorMaterialSoundRes.size());
	if (FloorMaterialIndex == Size)
	{
		FloorMaterialIndex = 0;
	}

	std::string_view SoundName = FloorMaterialSoundRes.at(FloorMaterialIndex);
	++FloorMaterialIndex;
	return SoundName;
}

void BaseActor::SetCenterBodyDPIndex(int _DPIndex)
{
	const std::shared_ptr<DS3DummyData>& pRes = DS3DummyData::Find(GetIDName());
	if (nullptr == pRes)
	{
		MsgBoxAssert("존재하지 않는 리소스로 세팅할 수 없습니다");
		return;
	}

	// 유효성 체크
	bool ResCheck = pRes->IsContainData(_DPIndex);
	if (false == ResCheck)
	{
		MsgBoxAssert("해당 값으로 세팅할 수 없습니다. 변수를 확인해주세요.");
		return;
	}

	CenterBodyIndex = _DPIndex;
}

void BaseActor::SetFloorMaterialSoundRes(std::string_view _ResName)
{
	std::string ResName = _ResName.data();
	size_t Index = ResName.find_last_of('.');
	if (std::string::npos == Index)
	{
		MsgBoxAssert("이름을 등록하지 못했습니다. 확장자까지 넣어주세요");
		return;
	}

	std::string Identify = ResName.substr(0, Index);

	std::string IdName = GetIDName();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Sound");
	Dir.MoveChild(IdName);

	bool FindCheck = false;
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".wav" });
	for (GameEngineFile& pFile : Files)
	{
		std::string FileName = pFile.GetFileName();
		if (std::string::npos != FileName.find(Identify))
		{
			FindCheck = true;
			FloorMaterialSoundRes.push_back(FileName);
			continue;
		}

		if (true == FindCheck)
		{
			return;
		}
	}

	if (false == FindCheck)
	{
		MsgBoxAssert("자료를 찾지 못했습니다.");
		return;
	}
}

void BaseActor::DrawRange(float _Range, const float4& _Color /*= float4::RED*/) const
{
	if (GameEngineLevel::IsDebug)
	{
		float4 WScale = float4(_Range, _Range, _Range, 1.0f);
		float4 WRot = Transform.GetWorldRotationEuler();
		float4 WPos = Transform.GetWorldPosition();

		GameEngineDebug::DrawSphere2D(WScale, WRot, WPos, _Color);
	}
}

std::string BaseActor::GetIDName() const
{
	int Id = GetID();
	std::string IDName = "c" + std::to_string(Id);
	return IDName;
}

void BaseActor::CalcuTargetAngle()
{
	if (nullptr == Target)
	{
		TargetAngle = 0.f;
		RotDir = Enum_RotDir::Not_Rot;
		return;
	}

	if (nullptr == Capsule)
	{
		TargetAngle = 0.f;
		RotDir = Enum_RotDir::Not_Rot;
		return;
	}

	float4 TargetPos = Target->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	// Y축 고려 X
	TargetPos.Y = MyPos.Y = 0.f;

	float4 FrontVector = float4(0.f, 0.f, 1.f, 0.f);
	FrontVector.VectorRotationToDegY(Capsule->GetDir());

	float4 LocationVector = (TargetPos - MyPos).NormalizeReturn();

	float4 Angle = DirectX::XMVector3AngleBetweenNormals(FrontVector.DirectXVector, LocationVector.DirectXVector);

	float4 RotationDir = DirectX::XMVector3Cross(FrontVector.DirectXVector, LocationVector.DirectXVector);

	TargetAngle = Angle.X * GameEngineMath::R2D;
	if (0.0f <= RotationDir.Y)
	{
		RotDir = Enum_RotDir::Right;
	}
	else
	{
		RotDir = Enum_RotDir::Left;
		TargetAngle *= -1.f;
	}
}

float BaseActor::GetTargetDistance() const
{
	if (nullptr == Target)
	{
		MsgBoxAssert("타겟이 존재하지 않습니다.");
		return 0.0f;
	}

	const float4 MyPos = Transform.GetWorldPosition();
	const float4 OtherPos = Target->Transform.GetWorldPosition();
	const float Dist = ContentsMath::GetVector3Length(OtherPos - MyPos).X;
	return Dist;
}

float4 BaseActor::GetTargetDirection() const
{
	if (nullptr == Target)
	{
		MsgBoxAssert("타겟이 존재하지 않습니다.");
		return float4::ZERO;
	}

	const float4 MyPos = Transform.GetWorldPosition();
	const float4 TargetPos = Target->Transform.GetWorldPosition();

	float4 Direction = TargetPos - MyPos;
	Direction.Normalize();
	return Direction;
}

void JumpTableManager::AddJumpTable(std::string_view _AnimationName, JumpTableInfo _JumpTableInfo)
{
	Owner->MainRenderer->SetFrameEvent(_AnimationName, _JumpTableInfo.StartFrame, std::bind(&JumpTableManager::PushJumpTable, this, _JumpTableInfo));
	Owner->MainRenderer->SetFrameEvent(_AnimationName, _JumpTableInfo.EndFrame, std::bind(&JumpTableManager::PopJumpTable, this, _JumpTableInfo));
	Owner->MainRenderer->SetAnimationChangeEvent(_AnimationName, std::bind(&JumpTableManager::Release, this));
}

void JumpTableManager::AddJumpTable(std::string_view _AnimationName, int _StartFrame, int _EndFrame, std::function<void()> _JumpTable)
{
	JumpTableInfo tJumpTableInfo;
	tJumpTableInfo.SetJumpTableInfo(_StartFrame, _EndFrame, _JumpTable);

	AddJumpTable(_AnimationName, tJumpTableInfo);
}

void JumpTableManager::Update()
{
	for (JumpTableInfo _CurTableInfo : RunJumpTable)
	{
		_CurTableInfo.JumpTable();
	}
}

void JumpTableManager::Release()
{
	RunJumpTable.clear();
}

void JumpTableManager::PushJumpTable(JumpTableInfo _JumpTableInfo)
{
	RunJumpTable.push_back(_JumpTableInfo);
}

void JumpTableManager::PopJumpTable(JumpTableInfo _JumpTableInfo)
{
	RunJumpTable.remove(_JumpTableInfo);
}