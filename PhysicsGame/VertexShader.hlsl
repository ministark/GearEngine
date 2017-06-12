float4x4 view_proj_matrix;
float4x4 texture_matrix;

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float3 Ptex : TEXCOORD0;
};

VS_OUTPUT main(float4 vPosition : POSITION)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	// Transform position to clip space
	Out.Pos = mul(view_proj_matrix, vPosition);
	// Transform Pshade
	Out.Ptex = mul(texture_matrix, vPosition);
	return Out;
}