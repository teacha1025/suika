namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
		uint4 color : COLOR0;
		float2 uv : TEXCOORD0;
	};

	struct PSInput
	{
		float4 position : SV_POSITION;
		uint4 color : COLOR0;
		float2 uv : TEXCOORD0;
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
    output.position = mul(input.position,  mt);
	output.position.x = output.position.x - 1;
	output.position.y = output.position.y + 1;
	output.position.w = 1;
    output.color = input.color;
	output.uv = input.uv;
    return output;
}

float4 ps_main( suika::PSInput input ) : SV_Target
{
    return g_texture.Sample(g_sampler, input.uv);
}