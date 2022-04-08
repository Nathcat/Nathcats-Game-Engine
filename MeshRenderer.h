#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef COMPONENT_H
#include "Component.h"
#endif

#ifndef MESH_H
#include "Mesh.h"
#endif

#ifndef MATERIAL_H
#include "Material.h"
#endif

#define MESHRENDERER_H


/// <summary>
/// Uses RENDERINGENGINE to render a mesh to the render target.
/// 
/// TODO
/// 
/// Required tasks:
///  - MESH class
///  - RENDERINGENGINE class
///  - SHADER class
///  - MATERIAL class
/// </summary>
class MeshRenderer : Component {
public:
	MESH* mesh;
	Material* material;

	/// <summary>
	/// Create a vertex buffer for this object that DirectX can use for rendering.
	/// 
	/// TODO
	/// 
	/// Required tasks:
	///  - Shader input struct/class
	/// </summary>
	/// <returns>A pointer to the vertex buffer</returns>
	ID3D11Buffer* CreateVertexBuffer() {

	}
};