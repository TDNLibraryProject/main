
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4x4 worldMatrix;

float3 viewPosition;

struct VSINPUT_COLOR
{
	float4 Pos : POSITION;
	float4 Col : COLOR;
};

VSINPUT_COLOR VS_COLOR( VSINPUT_COLOR In )
{
	float4x4 WVPMatrix;
	WVPMatrix = mul( worldMatrix, mul( viewMatrix, projectionMatrix ) );

	VSINPUT_COLOR Out;
	Out.Pos = mul( In.Pos, WVPMatrix );
	Out.Col = In.Col;
	return Out;
}

float4 PS_COLOR( VSINPUT_COLOR In ) : COLOR
{
	return In.Col;
}

technique linecopy
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = CCW;

		// シェーダ
		VertexShader = compile vs_3_0 VS_COLOR();
		PixelShader = compile ps_3_0 PS_COLOR();
	}
}
