#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

#define COMPONENT_H


/// <summary>
/// Abstract class that can be used to create components that are attached to 
/// game objects.
/// </summary>
class Component {
public:
	GameObject* gameObject;         // The GameObject that this object is attached to

	virtual ~Component() {};        // Destructor
	Component() {                   // Constructor
		Start(); 
	};

	virtual void Start() {};        // Start method
	virtual void Update() {};       // Update method
	virtual void FixedUpdate() {};  // FixedUpdate method
};