#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef COMPONENT_H
#include "Component.h"
#endif

#define TRANSFORM_H


/// <summary>
/// Transform component. Stores data about a game object's position, rotation, and scale
/// in the world.
/// </summary>
class Transform : Component {
public:
	XMVECTOR position = {0.0f, 0.0f, 0.0f};        // Position of the object
	XMVECTOR rotation = {0.0f, 0.0f, 0.0f, 0.0f};  // Rotation of the object
	XMVECTOR scale    = {1.0f, 1.0f, 1.0f};        // Scale of the object
	XMVECTOR forward;                              // Forward direction of this object
	XMVECTOR up;                                   // Upwards direction of this object
	XMVECTOR right;                                // Right direction of this object

	void FixedUpdate() override {
		forward = XMVector3Normalize(XMVectorMultiply(rotation, { 0.0f, 0.0f, 1.0f, 0.0f }));
		up = XMVector3Normalize(XMVectorMultiply(rotation, { 0.0f, 1.0f, 0.0f, 0.0f }));
		right = XMVector3Normalize(XMVectorMultiply(rotation, { 1.0f, 0.0f, 0.0f, 0.0f }));
	}

	/// <summary>
	/// Create a model transform matrix for this object.
	/// </summary>
	/// <returns>Model transform matrix (XMFLOAT4X4)</returns>
	XMFLOAT4X4 CreateModelMatrix() {
		XMFLOAT4X4 result;
		XMMATRIX mModelTransform = XMMatrixAffineTransformation(scale, {0.0f, 0.0f, 0.0f}, rotation, position);
		XMStoreFloat4x4(&result, mModelTransform);

		return result;
	}
};