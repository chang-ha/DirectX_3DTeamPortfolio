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
cbuffer RenderBaseInfo : register(b11)
{
    float4 ScreenSize;
    float4 BaseColor;
    int IsMask;
    int BaseColorOnly;
    int MaskMode;
    int BaseTemp2;
    float4 RendererScreenPos;
    float4 RenderScreenScale;
    float4 MaskScreenScale;
    float4 MaskPivot;
    float4 VertexUVPlus;
    float4 VertexUVMul;
    float DeltaTime;
    float AccDeltaTime;
    int Target0;
    int Target1;
    int Target2;
    int Target3;
    int Target4;
    int Target5;
    int Target6;
    int Target7;
};

