// transformations provided by the app:
float4x4 matWorldViewProj: WORLDVIEWPROJECTION;

// the format of our vertex data
struct VS_INPUT
{
	float4 Pos : POSITION;
	DWORD Col : COLOR0;
	float2 Tex : TEXCOORD1;
};

struct VS_OUTPUT
{
	float4 Pos  : POSITION;
	float2 Tex : TEXCOORD1;
};

// Vertex Shader - simply carry out transformation
VS_OUTPUT VS(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	Out.Pos = mul(In.Pos, matWorldViewProj);
	Out.Tex = In.Tex;
	return Out;
}

sampler Image;
// Pixel shader that calculates ambient light
float4 PS(VS_OUTPUT V): COLOR
{
	return tex2D (Image,V.Tex);
}

// Effect technique to be used
technique TVertexAndPixelShader
{
	pass P0
	{
		
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}