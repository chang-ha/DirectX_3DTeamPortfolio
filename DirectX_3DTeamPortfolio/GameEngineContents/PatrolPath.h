#pragma once

// Ό³Έν :
class PatrolPath
{
public:
	// constrcuter destructer
	PatrolPath();
	~PatrolPath();

	// delete Function
	PatrolPath(const PatrolPath& _Other) = delete;
	PatrolPath(PatrolPath&& _Other) noexcept = delete;
	PatrolPath& operator=(const PatrolPath& _Other) = delete;
	PatrolPath& operator=(PatrolPath&& _Other) noexcept = delete;

	void Init(const std::vector<float4>& _Paths, int _Index = 0);

	float4 GetNextPath(const float4& _ActorPos);

protected:
	bool IsArrive(const float4& _ActorPos) const;
	void ChangePath();

	void ValidityCheck(std::string_view _MSG = nullptr);

private:
	std::vector<float4> Paths;
	int CurIndex = 0;

	static constexpr float CognizanceRange = 5.0f;

};