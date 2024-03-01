#include "MeshBase_Header.fx"


struct DeferrdOut
{
    float4 DifColor : SV_Target1;
    float4 PosColor : SV_Target2;
    float4 NorColor : SV_Target3;
    float4 SpcColor : SV_Target4;
    float4 MatColor : SV_Target5;
    float4 WorldPosColor : SV_Target6;
};



void Mesh_PS_Update(inout PixelOutPut _Input, inout DeferrdOut _Result)
{
    float4 Color = BaseColor;
    
    Color.w = 1.0f;
    _Result.DifColor = Color;
    _Result.PosColor = _Input.VIEWPOSITION;
    _Result.WorldPosColor = _Input.WorldPOSITION;
           
    _Result.SpcColor = float4(1.f, 1.f, 1.f, 1.f);
     
       
    _Result.NorColor = _Input.VIEWNORMAL;
    _Result.NorColor.w = 1.f;
    
    
    if(Roughness < 0.0f)
    {
        _Result.MatColor.x = 0.5f; //Roughness
    }
    else
    {
        _Result.MatColor.x = Roughness;
    }
    
    if(Metalic < 0.0f)
    {
        _Result.MatColor.y = 0.5f; //Metalic
    }
    else
    {
        _Result.MatColor.y = Metalic;
    }
    _Result.MatColor.w = 1.0f;
    
}