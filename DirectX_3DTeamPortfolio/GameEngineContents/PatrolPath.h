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

	void Init(const std::vector<float4>& _Paths);

	float4 GetNextPath(const float4& _ActorPos);

protected:
	bool IsArrive() const;
	void ChangePath();

private:
	std::vector<float4> Paths;
	float4 CurPath;

	static constexpr float CognizanceRange = 5.0f;

};

