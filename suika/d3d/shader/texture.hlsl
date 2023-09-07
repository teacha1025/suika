namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
		uint4 color : COLOR0;
		float2 uv : TEXCOORD0;
		uint InstanceId : SV_InstanceID;
		float4x4 InstanceMatrix : MATRIX;
		//float2 dummy : TEXCOORD1;
	};

	struct PSInput
	{
		float4 position : SV_POSITION;
		uint4 color : COLOR0;
		float2 uv : TEXCOORD0;
		//float2 dummy : TEXCOORD1;
	};
}

cbuffer ConstantBuffer : register(b0)
{
    matrix mt;
}

Texture2D    g_texture : register(t0);
SamplerState g_sampler : register(s0);
suika::PSInput vs_main( suika::VSInput input )
{
    suika::PSInput output;
	float4 pos = input.position;
	pos = mul(pos,  input.InstanceMatrix);
    pos = mul(pos,  mt);

	output.position = pos;
    output.color = float4(input.color.x / 255.0f, input.color.y / 255.0f, input.color.z / 255.0f, input.color.w / 255.0f);
	output.uv = input.uv;
    return output;
}

float4 ps_main( suika::PSInput input ) : SV_Target
{
    return g_texture.Sample(g_sampler, input.uv);
}