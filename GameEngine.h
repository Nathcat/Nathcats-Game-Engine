#define GAMEENGINE_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef RENDERINGENGINE_H
#include "RenderingEngine.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

#include <vector>


/// <summary>
/// Facilitates the overarching process of the game engine.
/// </summary>
class GameEngine {
public:
	HWND hWnd;                            // Window handle
	RENDERINGENGINE* pRenderer;           // Pointer to the renderer
	std::vector<GameObject> gameObjects;  // Arraylist containing all game objects.

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="windowHandle">Handle for the window</param>
	GameEngine(HWND windowHandle) {
		hWnd = windowHandle;
		pRenderer = new RENDERINGENGINE(hWnd);
	};

	/// <summary>
	/// Performs a rendering frame process.
	/// </summary>
	void RenderingFrame() {
		for (int i = 0; i < gameObjects.size(); i++) {
			for (int x = 0; x < gameObjects.at(i).numberOfComponents; x++) {
				(gameObjects.at(i).pComponents + x)->Update();
			}
		}

		pRenderer->RenderFrame(gameObjects);
	};

	/// <summary>
	/// Performs a physics frame process.
	/// 
	/// TODO
	/// 
	/// Required tasks:
	///  - PHYSICS class
	///  - Rigidbody component
	/// </summary>
	void PhysicsFrame() {

	};
};