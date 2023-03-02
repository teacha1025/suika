namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
		ubyte4 color : COLOR0;
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
        return float4(input.color.x / 255.0f, input.color.y / 255.0f, input.color.z / 255.0f, input.color.w / 255.0f);
}