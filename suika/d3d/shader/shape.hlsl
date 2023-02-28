Texture2D g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
		float4 color : COLOR0;
		float2 uv : TEXCOORD0;
	};

	struct PSInput
	{
		float4 position : SV_POSITION;
		float4 color : COLOR0;
		float2 uv : TEXCOORD0;
	};

	float4 Transform2D(float2 pos, float2x4 t)
	{
		return float4((t._13_14 + (pos.x * t._11_12) + (pos.y * t._21_22)), t._23_24);
	}
}

cbuffer ConstantBuffer : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
}

suika::PSInput vs_main( suika::VSInput input )
{
    suika::PSInput output;
 
    output.position = mul(input.position,  world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    output.color = input.color;
	output.uv = input.uv;
    return output;
}

float4 ps_main( suika::PSInput input ) : SV_Target
{
        return input.color;
}