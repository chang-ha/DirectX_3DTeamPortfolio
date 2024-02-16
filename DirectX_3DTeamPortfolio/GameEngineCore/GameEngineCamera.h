#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>
#include <set>
#include "GameEngineRenderUnit.h"
#include "GameEngineAO.h"



struct ShadowAniInfo
{
	int IsShadowAnimation;
	int Temp0;
	int Temp1;
	int Temp2;
	float4x4 WorldViewProjectionMatrix;
};

// ���� :
class GameEngineCamera : public GameEngineActor, public DebugObject
{

	friend class GameEngineRenderUnit;
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
	static float FreeRotSpeed;
	static float FreeSpeed;


	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	void SetCameraOrder(int _Order);

	inline void SetProjectionType(EPROJECTIONTYPE _ProjectionType)
	{
		ProjectionType = _ProjectionType;
	}

	float4 GetWorldMousePos2D();

	void SetZoomValue(float _Value)
	{
		ZoomValue = _Value;
	}

	void AddZoomValue(float _Value)
	{
		ZoomValue += _Value;
	}

	bool IsFreeCamera() 
	{
		return IsFreeCameraValue;
	}

	EPROJECTIONTYPE GetProjectionType()
	{
		return ProjectionType;
	}


	void CameraTargetSetting(GameEngineTransform& _Target, const float4& _Pivot)
	{
		Pivot = _Pivot;
		Target = &_Target;
	}

	inline void SetCameraTargetPivot(const float4& _Pivot)
	{
		Pivot = _Pivot;
	}

	void CameraTargetReset()
	{
		Pivot = float4::ZERO;
		Target = nullptr;
	}

	bool IsCameraTargetting(GameEngineTransform* _pTransform)
	{
		if (Target == _pTransform)
		{
			return true;
		}

		return false;
	}

	float4 GetScreenMousePrevPos() { return ScreenMousePrevPos; }
	float4 GetScreenMousePos() { return ScreenMousePos; }
	float4 GetScreenMouseDir() { return ScreenMouseDir; }
	float4 GetScreenMouseDirNormal() { return ScreenMouseDirNormal; }

	template<typename EnumType>
	void SetZSort(EnumType _SortOrder)
	{
		ZSortMap.insert(static_cast<int>(_SortOrder));
	}

	void SetZSort(int _SortOrder) 
	{
		ZSortMap.insert(_SortOrder);
	}

	template<typename EnumType>
	void SetYSort(EnumType _SortOrder)
	{
		YSortMap.insert(static_cast<int>(_SortOrder));
	}

	void SetYSort(int _SortOrder)
	{
		YSortMap.insert(_SortOrder);
	}

	std::shared_ptr<class GameEngineRenderTarget> GetCameraAllRenderTarget()
	{
		return AllRenderTarget;
	}

	std::shared_ptr<class GameEngineRenderTarget> GetCameraForwardTarget()
	{
		return ForwardTarget;
	}

	std::shared_ptr<class GameEngineRenderTarget> GetCameraDeferredTarget()
	{
		return DeferredTarget;
	}

	std::shared_ptr<class GameEngineRenderTarget> GetCameraDeferredLightTarget()
	{
		return DeferredLightTarget;
	}
	
	std::shared_ptr<class GameEngineRenderTarget> GetCameraHBAOTarget()
	{
		return HBAO.HBAOTarget;
	}

	void SetFar(float _Far)
	{
		Far = _Far;
	}

	void SetNear(float _Near)
	{
		Near = _Near;
	}
	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> GetRenderers()
	{
		return Renderers;
	}

	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;
	
	
	float4 GetScreenPos(GameEngineTransform& Transform);

protected:
	void Start() override;

	void Update(float _Delta);

	void Render(float _DeltaTime);

	void AllReleaseCheck() override;

	
	bool InCamera(const GameEngineTransform& _Trans, class MeshBaseInfo _MeshBaseInfo);
	

private:
	float4 Pivot = float4::ZERO;
	GameEngineTransform* Target = nullptr;

	EPROJECTIONTYPE ProjectionType = EPROJECTIONTYPE::Orthographic;
	float Far = 100000.0f;
	float Near = 10.0f;
	float FOV = 60.0f;
	float ZoomValue = 0.0f;

	bool IsFreeCameraValue = false;

	int CameraOrder = 0;
	//std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;

	std::map<RenderPath, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>> Units;


	EPROJECTIONTYPE PrevProjectionType = EPROJECTIONTYPE::Orthographic;

	float4 ScreenMousePrevPos;
	float4 ScreenMousePos;
	float4 ScreenMouseDir;
	float4 ScreenMouseDirNormal;
	TransformData OriginData;

	// ī�޶� ����
	DirectX::BoundingFrustum CameraFrustum;

	std::set<int> ZSortMap;
	std::set<int> YSortMap;

	std::shared_ptr<class GameEngineRenderTarget> AllRenderTarget;

	// �������� ���� �����
	std::shared_ptr<class GameEngineRenderTarget> ForwardTarget;

	GameEngineAO HBAO;

	GameEngineRenderUnit DeferredLightRenderUnit;
	// ���۵��� �� �����
	std::shared_ptr<class GameEngineRenderTarget> DeferredLightTarget;

	GameEngineRenderUnit DeferredMergeUnit;

	std::shared_ptr<class GameEngineRenderTarget> DeferredTarget;

	ShadowAniInfo ShadowAniInfoValue;
	GameEngineRenderUnit ShadowRenderUnit;

	void CameraUpdate(float _DeltaTime);

	TransformData  UnitTransform;
};

