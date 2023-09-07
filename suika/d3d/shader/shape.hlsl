namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
		uint4 color : COLOR0;
		float2 uv : TEXCOORD0;
		uint InstanceId : SV_InstanceID;
		float4x4 InstanceMatrix : MATRIX;
	};

	struct PSInput
	{
		float4 position : SV_POSITION;
		float4 color : COLOR0;
		float2 uv : TEXCOORD0;
		//float2 dummy : TEXCOORD1;
	};

}

cbuffer ConstantBuffer : register(b0)
{
    matrix mt;
}

suika::PSInput vs_main( suika::VSInput input )
{
	suika::PSInput output;
	float4 pos = input.position;
	pos = mul(pos, input.InstanceMatrix);
	pos = mul(pos, mt);

	output.position = pos;
	output.color = float4(input.color.x / 255.0f, input.color.y / 255.0f, input.color.z / 255.0f, input.color.w / 255.0f);
	output.uv = input.uv;
	return output;
}

float4 ps_main( suika::PSInput input ) : SV_Target
{
	return input.color;
}