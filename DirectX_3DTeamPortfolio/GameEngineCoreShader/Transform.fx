// 버텍스 쉐이더 입니다.

// 외부에서 넣어주는 내가 만든 데이터들을 상수버퍼라고 부른다.
// dx11 쉐이더에서는 다음과 같이 선언해야 한다.
// 외부에서 세팅해주는 데이터다
// 상수버퍼가 슬롯개념에 해당합니다.
// 16개의 슬롯이 있고 꽂아주는 형식이다.
// 어떤 쉐이더가 동작할때 데이터를 16개까지 허용하고 있다.
// 넣어주는건 어떻게든 된다고 해도. 
// b는 buffer의 약자
// 0 슬롯의 index 실행시켜보니 14 까지 허용한다.
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;
	
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix; // 크
    float4x4 RotationMatrix; // 자
    float4x4 PositionMatrix; // 이
    float4x4 RevolutionMatrix; // 공
    float4x4 ParentMatrix; // 공

    float4x4 LocalWorldMatrix;
	// 월드 공간
    float4x4 WorldMatrix;


    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
    float4x4 ViewPort;

	// 로컬 => 월드 => 뷰 => 프로젝션 
    float4x4 WorldViewProjectionMatrix;
};

struct TransformDataStruct
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;
	
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix; // 크
    float4x4 RotationMatrix; // 자
    float4x4 PositionMatrix; // 이
    float4x4 RevolutionMatrix; // 공
    float4x4 ParentMatrix; // 공

    float4x4 LocalWorldMatrix;
	// 월드 공간
    float4x4 WorldMatrix;


    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
    float4x4 ViewPort;

	// 로컬 => 월드 => 뷰 => 프로젝션 
    float4x4 WorldViewProjectionMatrix;
};

//                 80바이트 500 
StructuredBuffer<TransformDataStruct> ArrTransform : register(t11);