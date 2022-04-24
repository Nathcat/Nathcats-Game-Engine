#define CAMERA_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef COMPONENT_H
#include "Component.h"
#endif

#ifndef TRANSFORM_H
#include "Transform.h"
#endif

#include <cmath>


class Camera : Component {
public:
	Transform* transform;
	float nearClip = 0.01f;
	float farClip = 100.0f;
	float fieldOfView = pi / 4.0f;

	void Start() override {
		transform = (Transform*)gameObject->GetComponent<Transform>();
	}

	/// <summary>
	/// Create a view transformation matrix.
	/// </summary>
	/// <returns>XMFLOAT4X4 representing a view transformation matrix.</returns>
	XMFLOAT4X4 CreateViewMatrix() {
		XMFLOAT4X4 result;
		XMMATRIX mViewMatrix = XMMatrixLookAtLH(transform->position, XMVectorAdd(transform->position, transform->forward), transform->up);
		XMStoreFloat4x4(&result, mViewMatrix);

		return result;
	}

	/// <summary>
	/// Create a projection transform matrix.
	/// </summary>
	/// <returns>XMFLOAT4X4 representing a projection transform matrix.</returns>
	XMFLOAT4X4 CreateProjectionMatrix() {
		float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
		XMFLOAT4X4 result;
		XMMATRIX mProjection = XMMatrixPerspectiveLH(fieldOfView, aspectRatio, nearClip, farClip);
		XMStoreFloat4x4(&result, mProjection);

		return result;
	}
};