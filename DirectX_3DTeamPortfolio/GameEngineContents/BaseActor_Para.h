#pragma once

class HitParameter
{
public:
	HitParameter() {}
	~HitParameter()
	{
		pAttacker = nullptr;
	}

	HitParameter(class BaseActor* _pAttacker, int _Stiffness = 0, Enum_DirectionXZ_Quat _eDir = Enum_DirectionXZ_Quat::Center)
		:pAttacker(_pAttacker), iStiffness(_Stiffness), eDir(_eDir)
	{

	}

public:
	class BaseActor* pAttacker = nullptr; // ���ݻ��
	Enum_DirectionXZ_Quat eDir = Enum_DirectionXZ_Quat::Center; // �´� DIR
	int iStiffness = 0; // ������

};

class BSCol_TransitionParameter
{
public:
	BSCol_TransitionParameter() {}
	~BSCol_TransitionParameter() {}
	BSCol_TransitionParameter(const float4& _S, const float4& _R, const float4& _T)
		:S(_S), R(_R), T(_T)
	{

	}


	float4 S = float4::ONE;
	float4 R = float4::ZERONULL;
	float4 T = float4::ZERO;
};

