cbuffer TransformMatrices : register(b0) {
	matrix model;
	matrix view;
	matrix projection;
};

cbuffer MaterialConstants : register(b1) {
	float4 emmisive;
};

struct VS_Input {
	float4 vertex : POSITION0;
};

struct PS_Input {
	float4 vertex : SV_POSITION;
};


PS_Input VShader(VS_Input input) {
	PS_Input output;

	output.vertex = input.vertex * ((model * view) * projection);

	return output;
};

float4 PShader(PS_Input input) {
	return emmisive;
};