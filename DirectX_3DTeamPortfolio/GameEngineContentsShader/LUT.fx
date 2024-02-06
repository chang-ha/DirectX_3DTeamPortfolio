struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // 픽셀쉐이더에 보내느 ㄴ역
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut LUT_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);
Texture2D LUTTex : register(t1);
SamplerState LUTTexSampler : register(s1);


float3 ApplyLut(float3 color)
{
    const float LUTSize = 64.0; // Assuming each tile is 64x64 pixels
    const float tileSize = 8.0; // 8 tiles per row/column
    const float numTiles = tileSize * tileSize; // Total number of tiles (slices)

    // Calculate size of each tile in texture coordinates
    float tileTexSize = 1.0 / tileSize;

    // Determine which tile based on the blue channel
    
    
    
    float bluelerpfactor = frac(color.b * (numTiles - 1));
    float blueSliceIndex = floor(color.b * (numTiles - 1));
    //float blueSliceIndexlerp = floor(color.b * (numTiles));
    
    // Calculate which row and column this tile is in
    float row = floor(blueSliceIndex / tileSize);
    float col = fmod(blueSliceIndex, tileSize);

    // Calculate base texture coordinates for this tile
    float2 baseTexCoord;
    baseTexCoord.x = col * tileTexSize;
    baseTexCoord.y = row * tileTexSize;
    
    float2 baseTexCoordlerp;
    baseTexCoordlerp.x = (col + 1) * tileTexSize;
    baseTexCoordlerp.y = row * tileTexSize;
    

    // Adjust red and green channels to fit within this tile
    float2 rgTexCoord;
    rgTexCoord.x = (color.r * (LUTSize - 1) + 0.5) / LUTSize;
    rgTexCoord.y = (color.g * (LUTSize - 1) + 0.5) / LUTSize;

    // Final texture coordinate combines base tile location with adjusted RG coordinate
    float2 finalTexCoord = baseTexCoord + rgTexCoord * tileTexSize;
    float2 finalTexCoordlerp = baseTexCoordlerp + rgTexCoord * tileTexSize;
    
    // 블루값을 러프로 매끄럽게
    //float3 lutcolor = lerp(LUTTex.Sample(LUTTexSampler, finalTexCoord).rgb, LUTTex.Sample(LUTTexSampler, finalTexCoordlerp).rgb, bluelerpfactor);
    

    return LUTTex.Sample(LUTTexSampler, finalTexCoord).rgb;
}


float4 LUT_PS(PixelOutPut _Input) : SV_Target0
{
    // return float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
 
    
    return float4(ApplyLut(Color.rgb),1.0f);
}