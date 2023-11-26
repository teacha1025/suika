namespace suika
{
	struct VSInput
	{
		float4 position : POSITION;
        float4 color : COLOR0;
		float2 uv : TEXCOORD0;
		
        float4x4 ins_matrix : INS0_MATRIX;
        float2x2 ins_uv : INS1_UV;
        uint instance_id : SV_InstanceID;
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
    pos = mul(pos, input.ins_matrix);
	pos = mul(pos, mt);

	output.position = pos;
	output.color = input.color;
    float2x2 uv_rb = float2x2(input.ins_uv._11, 0.0f, 0.0f, input.ins_uv._22);
    float2 uv_lt = float2(input.ins_uv._21, input.ins_uv._12);
    output.uv = mul(input.uv, uv_rb) + uv_lt;
	return output;
}

float4 ps_main( suika::PSInput input ) : SV_Target
{
	return input.color;
}