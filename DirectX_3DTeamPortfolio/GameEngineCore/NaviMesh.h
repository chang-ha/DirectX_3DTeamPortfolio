#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <vector>

struct NaviTri
{
	union 
	{
		struct 
		{
			float4 V0;
			float4 V1;
			float4 V2;
		};
		float4 Arr[3];
	};

	int Index = -1;
	std::vector<int> OtherTriIndex;
};

// Ό³Έν :
class NaviMesh
{
public:
	// constrcuter destructer
	NaviMesh();
	~NaviMesh();

	// delete Function
	NaviMesh(const NaviMesh& _Other) = delete;
	NaviMesh(NaviMesh&& _Other) noexcept = delete;
	NaviMesh& operator=(const NaviMesh& _Other) = delete;
	NaviMesh& operator=(NaviMesh&& _Other) noexcept = delete;

	void Create(std::vector<float4> _Tris);

protected:

private:
	std::vector<NaviTri> Tris;

};

class PlayerNavi 
{
	int CurTriIndex;
};
