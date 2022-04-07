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
	XMVECTOR position = {0.0f, 0.0f, 0.0f};    // Position of the object
	XMVECTOR rotation = {0.0f, 0.0f, 0.0f};    // Rotation of the object
	XMVECTOR scale    = {1.0f, 1.0f, 1.0f};    // Scale of the object
};