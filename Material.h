#define MATERIAL_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif


/// <summary>
/// Material class, this will be attached to a MeshRenderer to define how 
/// a mesh should appear.
/// 
/// Note, this may change at some point in the future, I would eventually
/// like to implement a system where the parameters in the shader program
/// define the parameters in the material, but that is outside of the scope
/// right now.
/// </summary>
class Material {
public:
	D3DXCOLOR emmisive, diffuse, ambient;
	float shininess;
	Shader* pShader;

	Material(D3DXCOLOR _emmisive, D3DXCOLOR _diffuse, D3DXCOLOR _ambient, float _shininess, Shader* _pShader) {
		emmisive = _emmisive;
		diffuse = _diffuse;
		ambient = _ambient;
		shininess = _shininess;
		pShader = _pShader;
	}
};