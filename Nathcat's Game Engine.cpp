#include "framework.h"


/// <summary>
/// Starting point for win32 applications.
/// </summary>
/// <param name="hInstance">Handle to the program's executable, ie the exe in memory.</param>
/// <param name="hPrevInstance">This will always be NULL for win32 applications.</param>
/// <param name="lpCmdLine">Points to a single string containing command line arguments.</param>
/// <param name="cmdShow">This is passed to the call to ShowWindow in this function.</param>
/// <returns>Returns the wParam of a quit message.</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow) {
	HWND hWnd;                                 // Window handle
	WNDCLASSEX wc;                             // Struct that holds information about the window class

	ZeroMemory(&wc, sizeof(WNDCLASSEX));       // Clear the window class struct

	wc.cbSize = sizeof(WNDCLASSEX);            // Define the size of the struct
	wc.style = CS_HREDRAW | CS_VREDRAW;        // Redraw horizontally and vertically
	wc.lpfnWndProc = WindowProc;               // Set the process function that handles messages
	wc.hInstance = hInstance;                  // Set the application instance
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // Set the cursor that will be displayed over the window
	wc.lpszClassName = WINDOW_CLASS_NAME;      // Set the class name

	RegisterClassEx(&wc);                      // Register the window class


	RECT wr = {                                // Create a window rect, which defines the size and position of the window
		0,                                     // x position of the window
		0,                                     // y position of the window
		SCREEN_WIDTH,                          // Width of the window 
		SCREEN_HEIGHT                          // Height of the window
	};
	AdjustWindowRect(                          // Set the window rect
		&wr,                                   // Pointer to the RECT struct
		WS_OVERLAPPEDWINDOW,                   // Style of the window
		FALSE                                  // Are we using a menu? No, so this parameter is FALSE.
	);

	hWnd = CreateWindowEx(                     // Create a window and an application handle
		NULL,
		WINDOW_CLASS_NAME,                     // Window class name, defined in "framework.h"
		L"Nathcat's Game Engine",              // Title of the window, displayed at the top of the window
		WS_OVERLAPPEDWINDOW,                   // Window style
		0,                                     // Window x position
		0,                                     // Window y position
		wr.right - wr.left,                    // Width
		wr.bottom - wr.top,                    // Height
		NULL,                                  // Parent window, if applicable
		NULL,                                  // Menu, if applicable
		hInstance,                             // Application handle, passed to this function when the application is opened
		NULL);                                 // This is used when we have multiple windows, which we don't, so set to NULL

	ShowWindow(hWnd, cmdShow);

	// A message is an event that is passed to the application for handling,
	// for example, resizing the window, or clicking the exit button.
	MSG msg;
	while (TRUE) {

		// PeekMessage checks to see if there is a message on the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}

		}
	}

	return msg.wParam;
};

/// <summary>
/// Windows proccess function, handles event messages.
/// </summary>
/// <param name="hWnd">Window/application handle</param>
/// <param name="message">The event message</param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns>Result code of the event processing</returns>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Handle window events
	switch (message) {

	case WM_DESTROY: {  // If the window exit button has been clicked, exit the application
		PostQuitMessage(0);
		return 0;
	} break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);  // Default event handle process
};
