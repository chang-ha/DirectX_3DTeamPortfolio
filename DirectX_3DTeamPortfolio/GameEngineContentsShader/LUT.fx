cbuffer LutInfo : register(b12)
{
    float Lutweight; 
    float Def1;
    float Def2;
    float Def3;
};


struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
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


    // Calculate exact position in the LUT based on blue channel
    float exactBlueSliceIndex = color.b * (numTiles - 1);

    // Determine indices of the two closest slices
    float lowerIndex = floor(exactBlueSliceIndex);
    float upperIndex = lowerIndex + 1.0;
    
    // Calculate blend factor between two slices
    float blendFactor = frac(exactBlueSliceIndex);

    // Calculate row and column for both slices
    float2 lowerTile;
    lowerTile.x = fmod(lowerIndex, tileSize);
    lowerTile.y = floor(lowerIndex / tileSize);

    float2 upperTile;
    upperTile.x = fmod(upperIndex, tileSize);
    upperTile.y = floor(upperIndex / tileSize);

    // Adjust red and green channels to fit within a tile
    float2 rgTexCoord;
    rgTexCoord.x = (color.r * (LUTSize - 1) + 0.5) / LUTSize;
    rgTexCoord.y = (color.g * (LUTSize - 1) + 0.5) / LUTSize;

    // Calculate final texture coordinates for both slices
    float2 lowerFinalTexCoord = (lowerTile + rgTexCoord) * tileTexSize;
    float2 upperFinalTexCoord = (upperTile + rgTexCoord) * tileTexSize;

    // Sample both slices
    float3 colorLowerSlice = LUTTex.Sample(LUTTexSampler, lowerFinalTexCoord).rgb;
    float3 colorUpperSlice = LUTTex.Sample(LUTTexSampler, upperFinalTexCoord).rgb;

    // Linearly interpolate between the two samples based on blend factor
    return lerp(colorLowerSlice, colorUpperSlice, blendFactor);
    
    ////
    
    
}


float4 LUT_PS(PixelOutPut _Input) : SV_Target0
{
    // return float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    float4 LutColor = float4(ApplyLut(Color.rgb), 1.0f);
 
    float4 Result = float4(lerp(Color.xyz, LutColor.xyz, Lutweight), 1.0f);
    
    return Result;

}