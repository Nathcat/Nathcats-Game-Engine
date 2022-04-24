#define GAMEOBJECT_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef COMPONENT_H
#include "Component.h"
#endif


/// <summary>
/// Represents a game object.
/// </summary>
class GameObject {
public:
	Component* pComponents;  // Pointer to an array of components attached to this game object.
	int numberOfComponents;  // Number of components in the array

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="p_Components">Pointer to an array of components that are to be attached to this game object</param>
	/// <param name="NumberOfComponents">The number of components in the array</param>
	GameObject(Component* p_Components, int NumberOfComponents) {
		pComponents = p_Components;
		numberOfComponents = NumberOfComponents;
	};

	/// <summary>
	/// Gets a component object from the array of components attached to this game object.
	/// </summary>
	/// <typeparam name="ComponentType">The Component type.</typeparam>
	/// <returns>The component pointer, or a nullptr</returns>
	template<class ComponentType> Component* GetComponent() {
		Component* result = nullptr;

		for (int i = 0; i < numberOfComponents; i++) {
			if (isinstance<ComponentType>(*(pComponents + i))) {
				result = pComponents + i;
			}
		}

		return result;
	}
};