#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#define COMPONENT_H


/// <summary>
/// Abstract class that can be used to create components that are attached to 
/// game objects.
/// </summary>
class Component {
public:
	virtual ~Component() {};        // Destructor
	Component() { Start(); };       // Constructor

	virtual void Start() {};        // Start method
	virtual void Update() {};       // Update method
	virtual void FixedUpdate() {};  // FixedUpdate method
};