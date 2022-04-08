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

#ifndef CAMERA_H
#include "Camera.h"
#endif

#ifndef TRANSFORM_H
#include "Transform.h"
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
	/// <param name="dev">Pointer to DirectX device</param>
	/// <param name="devcon">Pointer to DirectX device context</param>
	/// <returns>A pointer to the vertex buffer</returns>
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* dev, ID3D11DeviceContext* devcon) {
		ID3D11Buffer* buffer;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));                                           // Clear the buffer description struct

		bd.Usage = D3D11_USAGE_DYNAMIC;                                                       // Access from CPU and GPU
		bd.ByteWidth = material->GetSizeOfElementsArray() * mesh->numberOfVertices;           // Set the byte width of the buffer
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;                                              // Set as vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;                                           // Allow the CPU to write to the buffer

		dev->CreateBuffer(&bd, NULL, &buffer);                                                // Create the buffer

		D3D11_MAPPED_SUBRESOURCE ms;                                                          // Mapped buffer
		devcon->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);                        // Map the buffer, preventing the GPU from using it while vertices are copied to it
		memcpy(ms.pData, mesh->pVertices, material->GetSizeOfElementsArray() * mesh->numberOfVertices);  // Copy the vertex data to the buffer
		devcon->Unmap(buffer, NULL);                                                          // Unmap the buffer

		return buffer;
	}

	/// <summary>
	/// Creates a buffer of transform matrices used to transform vertices onto the screen.
	/// </summary>
	/// <param name="dev">Pointer to the DirectX device.</param>
	/// <param name="devcon">Pointer to the DirectX device context.</param>
	/// <returns>Pointer to a buffer object.</returns>
	ID3D11Buffer* CreateTransformMatricesBuffer(Transform transform, Camera camera, ID3D11Device* dev, ID3D11DeviceContext* devcon) {
		TransformMatricesBuffer matrices = {
			transform.CreateModelMatrix(),
			camera.CreateViewMatrix(),
			camera.CreateProjectionMatrix()
		};
		
		ID3D11Buffer* buffer;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));                                           // Clear the buffer description struct

		bd.Usage = D3D11_USAGE_DYNAMIC;                                                       // Access from CPU and GPU
		bd.ByteWidth = sizeof(TransformMatricesBuffer);                                       // Set the byte width of the buffer
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;                                            // Set as vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		dev->CreateBuffer(&bd, NULL, &buffer);

		D3D11_MAPPED_SUBRESOURCE ms;                                                          // Mapped buffer
		devcon->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);                        // Map the buffer, preventing the GPU from using it while vertices are copied to it
		memcpy(ms.pData, &matrices, sizeof(TransformMatricesBuffer));                         // Copy the vertex data to the buffer
		devcon->Unmap(buffer, NULL);                                                          // Unmap the buffer

		return buffer;
	}
};

typedef struct TransformMatricesBuffer {
	XMFLOAT4X4 model;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};