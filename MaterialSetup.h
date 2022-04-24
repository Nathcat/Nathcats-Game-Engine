#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef COMPONENT_H
#include "Component.h"
#endif

#ifndef MATERIAL_H
#include "Material.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif

class MaterialSetup : Component {
public:
	void Start() override {
		D3D11_INPUT_ELEMENT_DESC* desc = new D3D11_INPUT_ELEMENT_DESC[1] {
			{"POSITION", 0, SHADERINPUT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		Shader defaultShader(
			pGameEngine->pRenderer->dev, 
			(LPCWSTR) "default.shader", 
			(LPSTR) "VShader", 
			(LPSTR) "PShader",
			desc,
			1);

		Material material(&defaultShader);
		// Check pull request #5 on GitHub
	}
};