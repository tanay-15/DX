// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	//float4 color		: COLOR;
	float3 normal		: NORMAL;
	float2 UV			: TEXCOORD;
};


struct DirectionalLight
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};



struct DirectionalLight1
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};

cbuffer externalData : register(b0)
{
	DirectionalLight light;
	DirectionalLight1 dlight;
};

Texture2D wallTexture  : register(t0);
SamplerState basicSampler : register(s0);

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);

	float4 surfaceColor = wallTexture.Sample(basicSampler, input.UV);


	float3 lightDirection = -normalize(light.Direction);
	float lightAmount = dot(input.normal, lightDirection);
	lightAmount = saturate(lightAmount);
	float3 finalColor = surfaceColor * (light.DiffuseColor * lightAmount + light.AmbientColor);


	float3 lightDirection1 = -normalize(dlight.Direction);
	float lightAmount1 = dot(input.normal, lightDirection1);
	lightDirection1 = saturate(lightAmount1);
	float3 finalColor1 = surfaceColor * (dlight.DiffuseColor *lightAmount1 + dlight.AmbientColor);


	return float4((finalColor + finalColor1).xyz, 1);
	//return float4(input.normal, 1);
	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	//return input.color;
	//return float4(pointNdotL);
	//return float4((light.DiffuseColor * lightAmount + light.AmbientColor).xyz, 1);
	//return float4(1, 0, 0, 1);
}