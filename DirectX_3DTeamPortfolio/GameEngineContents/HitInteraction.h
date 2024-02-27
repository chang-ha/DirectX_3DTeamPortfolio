#pragma once

// 설명 : 충돌처리를 관리해주는 객체입니다. 
//      내려받아서 충돌방식을 정의해주세요.
// 주의 사항 : 액터 내 충돌체를 지우고 사용하면 100% 터집니다. 지울때 함께 Release 해주세요.
class HitInteraction : public GameEngineObjectBase
{
public:
	// constrcuter destructer
	HitInteraction();
	~HitInteraction();

	// delete Function
	HitInteraction(const HitInteraction& _Other) = delete;
	HitInteraction(HitInteraction&& _Other) noexcept = delete;
	HitInteraction& operator=(const HitInteraction& _Other) = delete;
	HitInteraction& operator=(HitInteraction&& _Other) noexcept = delete;

	void On() override;
	void Off() override;

	// 액터 포인터와 콜리전을 요구
	void Init(class BaseActor* _pParent, GameEngineCollision* _pCol);

	virtual void CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness = 0) = 0; // 충돌 To Body << 쓰지 않으셔도 상관없습니다.
	virtual void CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness = 0) {} // 충돌 To Shield << 쓰지 않으셔도 상관없습니다. Body와 작동하는 방식이 달라서 분리했습니다.

	void RecordCollision(class BaseActor* _pActor); // 충돌한 객체를 보관합니다. 나중에 ResetRecord로 초기화 시켜야합니다.
	bool IsContain(class BaseActor* _pActor) const; // 충돌 했는지 알려줍니다.
	void ResetRecord(); // 충돌 기록을 초기화합니다.

	void Release(); // 이 객체를 들고있는 액터가 따로 이 함수를 호출하지않아도 잘 지워지지만 혹시 모르니 해주세요..

protected:
	// 유효한지 검사해줍니다.
	virtual void ValidityCheck(std::string_view _MSG = "");

protected:
	class GameEngineCollision* pCollision = nullptr;
	class BaseActor* pParent = nullptr;

private:
	std::set<class BaseActor*> HitRecord;

};

