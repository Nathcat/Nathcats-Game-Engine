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
/// Users should create other Materials that inherit from this class
/// that they can use with their own shaders.
/// </summary>
class Material {
public:
	Shader* pShader;

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="_pShader"></param>
	Material(Shader* _pShader) {
		pShader = _pShader;
	}
};