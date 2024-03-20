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

	void Init(const std::vector<float4>& _Paths, int _Index = 0, bool _IsOneWay = false);

	bool IsArrive(const float4& _ActorPos) const;
	float4 GetCurPath();
	void ChangePath();

protected:
	bool OverIndex();

	void ValidityCheck(std::string_view _MSG = "");

private:
	std::vector<float4> Paths;
	int CurIndex = 0;
	int iDir = 1;

	bool bOneWay = false;

};