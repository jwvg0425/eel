TextureCube gCubeMap;

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

cbuffer CubeMapCBuffer
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
	float3	gEyePosW;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float3 PosW    : POSITION;
	float3 NormalW : NORMAL;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.PosW = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);

	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float3 toEye = gEyePosW - pin.PosW;
	float distToEye = length(toEye);

	toEye /= distToEye;

	pin.NormalW = normalize(pin.NormalW);

	float3 reflectionVector = reflect(-toEye, pin.NormalW);
	float4 reflectColor = gCubeMap.Sample(samLinear, reflectionVector);

	return reflectColor;
}

technique11 Mapping
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}