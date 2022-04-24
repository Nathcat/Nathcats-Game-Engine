#pragma once

#define MESH_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif


/// <summary>
/// Stores a mesh for an object.
/// </summary>
class MESH {
public:
	XMVECTOR* pVertices;  // Pointer to an array of vertices
	int numberOfVertices;    // The number of vertices in the array
	XMVECTOR* pNormals;   // Pointer to an array of normals

	~MESH();

	/// <summary>
	/// Create a MESH object.
	/// </summary>
	/// <param name="p_Vertices">Pointer to an array of vertices</param>
	/// <param name="NumberOfVertices">The number of vertices in the array</param>
	/// <param name="p_Triangles">Pointer to an array of triangles</param>
	/// <param name="p_Normals">Pointer to an array of normals, defaults to nullptr</param>
	MESH(XMVECTOR* p_Vertices, int NumberOfVertices, XMVECTOR* p_Normals = nullptr) {
		pVertices = p_Vertices;
		numberOfVertices = NumberOfVertices;

		if (p_Normals == nullptr) {
			this->CalculateNormals();
		}
		else {
			pNormals = p_Normals;
		}
	}

	/// <summary>
	/// Calculate the normals of each triangle face in the mesh.
	/// </summary>
	void CalculateNormals() {
		pNormals = new XMVECTOR[(int)floor(numberOfVertices / 3)];

		int normalCounter = 0;
		int i = 0;
		while (i < numberOfVertices) {
			XMVECTOR u = *(pVertices + i + 1) - *(pVertices + i);
			XMVECTOR v = *(pVertices + i + 2) - *(pVertices + i);
			*(pNormals + normalCounter) = XMVector3Cross(u, v);

			normalCounter++;
			i += 3;
		}
	}
};
