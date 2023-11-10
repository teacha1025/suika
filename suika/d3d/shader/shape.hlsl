namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
        float4 color : COLOR0;
		float2 uv : TEXCOORD0;
		
		float4x4 InstanceMatrix : INS_MATRIX;
		float4 InstanceColor : INS_COLOR;
        uint InstanceId : SV_InstanceID;
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
	output.color = input.color;
	output.uv = input.uv;
	return output;
}

float4 ps_main( suika::PSInput input ) : SV_Target
{
	return input.color;
}