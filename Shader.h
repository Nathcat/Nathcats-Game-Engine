#define SHADER_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif


/// <summary>
/// Shader class, this class handles a Shader program.
/// </summary>
class Shader {
public:
	ID3D11VertexShader* pVS;
	ID3D11PixelShader* pPS;
	ID3D11InputLayout* pLayout;

	Shader(ID3D11Device* dev, LPCWSTR filename, LPSTR vertexShaderName, LPSTR pixelShaderName, D3D11_INPUT_ELEMENT_DESC* desc, int numberOfElementsInDesc) {
		// Compile the vertex and pixel shaders from the shader file
		ID3D10Blob* VS;
		ID3D10Blob* PS;

		HRESULT a = D3DX11CompileFromFile(filename, 0, 0, vertexShaderName, "vs_4_0", D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY, 0, 0, &VS, 0, 0);
		HRESULT b = D3DX11CompileFromFile(filename, 0, 0, pixelShaderName, "ps_4_0", D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY, 0, 0, &PS, 0, 0);

		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &(Shader::pVS));
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &(Shader::pPS));

		// Create the input layout
		dev->CreateInputLayout(desc, numberOfElementsInDesc, VS->GetBufferPointer(), VS->GetBufferSize(), &(Shader::pLayout));
	}
	~Shader() {
		pLayout->Release();
		pVS->Release();
		pPS->Release();
	}

	void SetAsActiveShader(ID3D11DeviceContext* devcon) {
		devcon->VSSetShader(pVS, 0, 0);
		devcon->PSSetShader(pPS, 0, 0);
		devcon->IASetInputLayout(pLayout);
	}
};
