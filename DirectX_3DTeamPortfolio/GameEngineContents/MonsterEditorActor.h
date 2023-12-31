#pragma once

// ���� :
class MonsterEditorActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterEditorActor();
	~MonsterEditorActor();

	// delete Function
	MonsterEditorActor(const MonsterEditorActor& _Other) = delete;
	MonsterEditorActor(MonsterEditorActor&& _Other) noexcept = delete;
	MonsterEditorActor& operator=(const MonsterEditorActor& _Other) = delete;
	MonsterEditorActor& operator=(MonsterEditorActor&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineFBXRenderer> GetRenderer()
	{
		if (nullptr == Renderer)
		{
			MsgBoxAssert("�������� �������� �ʾҽ��ϴ�.");
			return nullptr;
		}

		return Renderer;
	}
		
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineFBXRenderer> Renderer;
	float AnimationInter = 0.05f;

};

