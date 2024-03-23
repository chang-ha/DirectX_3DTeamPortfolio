#pragma once

enum class Enum_AlertType
{
	YouDie,
	Destroy,
	BoneFire,
};

// Ό³Έν :

class UIAlertMaanger : public GameEngineActor
{
public:
	// constrcuter destructer
	UIAlertMaanger();
	~UIAlertMaanger();

	// delete Function
	UIAlertMaanger(const UIAlertMaanger& _Other) = delete;
	UIAlertMaanger(UIAlertMaanger&& _Other) noexcept = delete;
	UIAlertMaanger& operator=(const UIAlertMaanger& _Other) = delete;
	UIAlertMaanger& operator=(UIAlertMaanger&& _Other) noexcept = delete;

	static void CallAlert(Enum_AlertType _Type);


protected:
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(GameEngineLevel* _NextLeve) override;

	void DetectOffAlert();

public:
	static bool Alerting;

private:
	static std::list<Enum_AlertType> CallMSG;

	class UIAlert* UIAlertPointer = nullptr;

};

