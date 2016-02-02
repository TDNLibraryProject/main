
float4x4 viewMatrix;
float4x4 projectionMatrix;

float4x4 worldMatrix;

float3 viewPosition;

struct VSINPUT
{
	float4 Pos : POSITION;
};

VSINPUT VS_COLOR( VSINPUT In )
{
	float4x4 WVPMatrix;
	WVPMatrix = mul( worldMatrix, mul( viewMatrix, projectionMatrix ) );

	VSINPUT Out;
	Out.Pos = mul( In.Pos, WVPMatrix );
	return Out;
}

float4 PS_COLOR( VSINPUT In ) : COLOR
{
	return float4( 1, 1, 1, 1 );
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
