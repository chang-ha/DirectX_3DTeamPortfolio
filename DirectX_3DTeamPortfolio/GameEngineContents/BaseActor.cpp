#include "PreCompile.h"
#include "BaseActor.h"

#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"
#include "ContentsDebug.h"


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
}

void BaseActor::Release()
{
	MainRenderer = nullptr;
	SocketCollisions.clear();
	Target = nullptr;
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

void BaseActor::DebugFlag()
{
	bool HitValue = IsFlag(Enum_ActorFlag::Hit);
	bool DeathValue = IsFlag(Enum_ActorFlag::Death);
	bool ParryPossible = IsFlag(Enum_ActorFlag::Parrying);
	int a = 0;
}


void BaseActor::AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum)
{
	BoneIndex.insert(std::make_pair(_BoneType, _BoneNum));
}

/// <summary>
/// 엔진에서 정의한 해시와 본 인덱스를 매핑시킨 데이터를 반환합니다.
/// </summary>
/// <param name="_BoneType">해시 정보</param>
/// <returns> Default Value : 0 </returns>
int BaseActor::GetBoneIndex(Enum_BoneType _BoneType)
{
	std::unordered_map<Enum_BoneType, int>::const_iterator FindIter = BoneIndex.find(_BoneType);
	if (FindIter == BoneIndex.end())
	{
		return 0;
	}

	return FindIter->second;
}

float4x4& BaseActor::GetBoneMatrixToType(Enum_BoneType _BoneType)
{
	int Index = GetBoneIndex(_BoneType);
	return GetBoneMatrixToIndex(Index);
}

float4x4& BaseActor::GetBoneMatrixToIndex(int _Index)
{
	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	return BoneMats[_Index];
}

std::shared_ptr<BoneSocketCollision> BaseActor::CreateSocketCollision(Enum_CollisionOrder _Order, int _SocketIndex, std::string _ColName)
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
	NewCol->Off();
	SocketCollisions.insert(std::make_pair(_SocketIndex, NewCol));
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

std::shared_ptr<BoneSocketCollision> BaseActor::FindSocketCollision(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	return GetSocketCollision(SocketIndex);
}

void BaseActor::OnSocketCollision(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	OnSocketCollision(SocketIndex);
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


void BaseActor::OffSocketCollision(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	OffSocketCollision(SocketIndex);
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

std::string BaseActor::GetEventPath(int _ID)
{
	if (EMPTY_ID == _ID)
	{
		return std::string();
	}

	std::string IDName = std::string("c") + std::to_string(_ID);

	GameEnginePath path;
	path.MoveParentToExistsChild("ContentsResources");
	path.MoveChild("ContentsResources");
	path.MoveChild("Mesh");
	path.MoveChild(IDName);
	path.MoveChild("Animation");
	return path.GetStringPath();
}

bool BaseActor::LoadEvent(int _ID)
{
	std::string Path = GetEventPath(_ID);
	if (Path.empty())
	{
		return false;
	}

	GameEngineDirectory Dir(Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ FrameEventHelper::GetExtName().data() });
	for (GameEngineFile& pFile : Files)
	{
		FrameEventHelper::Load(pFile.GetStringPath());
	}

	return true;
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