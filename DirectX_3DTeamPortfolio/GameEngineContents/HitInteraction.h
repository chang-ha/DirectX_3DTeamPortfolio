#pragma once

// ���� : �浹ó���� �������ִ� ��ü�Դϴ�. 
//      �����޾Ƽ� �浹����� �������ּ���.
// ���� ���� : ���� �� �浹ü�� ����� ����ϸ� 100% �����ϴ�. ���ﶧ �Բ� Release ���ּ���.
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

	// ���� �����Ϳ� �ݸ����� �䱸
	void Init(class BaseActor* _pParent, GameEngineCollision* _pCol);

	virtual void CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness = 0) = 0; // �浹 To Body << ���� �����ŵ� ��������ϴ�.
	virtual void CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness = 0) {} // �浹 To Shield << ���� �����ŵ� ��������ϴ�. Body�� �۵��ϴ� ����� �޶� �и��߽��ϴ�.

	void RecordCollision(class BaseActor* _pActor); // �浹�� ��ü�� �����մϴ�. ���߿� ResetRecord�� �ʱ�ȭ ���Ѿ��մϴ�.
	bool IsContain(class BaseActor* _pActor) const; // �浹 �ߴ��� �˷��ݴϴ�.
	void ResetRecord(); // �浹 ����� �ʱ�ȭ�մϴ�.

	void Release(); // �� ��ü�� ����ִ� ���Ͱ� ���� �� �Լ��� ȣ�������ʾƵ� �� ���������� Ȥ�� �𸣴� ���ּ���..

protected:
	// ��ȿ���� �˻����ݴϴ�.
	virtual void ValidityCheck(std::string_view _MSG = "");

protected:
	class GameEngineCollision* pCollision = nullptr;
	class BaseActor* pParent = nullptr;

private:
	std::set<class BaseActor*> HitRecord;

};

