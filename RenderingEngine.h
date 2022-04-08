#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef GAMEOBJECT_H
#include "GameObject.h"
#endif

#ifndef MESHRENDERER_H
#include "MeshRenderer.h"
#endif

#ifndef CAMERA_H
#include "Camera.h"
#endif

#include <vector>


class RenderingEngine {
public:
	HWND hWnd;                                // Window handle
	ID3D11Device* dev;                        // DirectX device
	ID3D11DeviceContext* devcon;              // DirectX device context
	IDXGISwapChain* swapchain;                // DXGI swapchain
	ID3D11RenderTargetView* backbuffer;       // The backbuffer render target
	D3D11_VIEWPORT viewport;                  // The viewport
	Camera camera;                            // Active camera

	/// <summary>
	/// Constructor with windowHandle parameter.
	/// </summary>
	/// <param name="windowHandle">Window handle</param>
	RenderingEngine(HWND windowHandle) {
		hWnd = windowHandle;                                    // Assign the window handle

		DXGI_SWAP_CHAIN_DESC scd;                               // Create a struct to hold information about the swap chain

		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));         // Clear the struct for use

		// fill the swap chain description struct
		scd.BufferCount = 1;                                    // one back buffer
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
		scd.BufferDesc.Width = SCREEN_WIDTH;                    // Set the width of the buffer
		scd.BufferDesc.Height = SCREEN_HEIGHT;                  // Set the height of the buffer
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		scd.OutputWindow = hWnd;                                // the window to be used
		scd.SampleDesc.Count = 4;                               // how many multisamples
		scd.Windowed = TRUE;                                    // windowed/full-screen mode
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // Allow switching between fullscreen and windowed mode

		D3D11CreateDeviceAndSwapChain(                          // Create a device, device context and swap chain using the information in the scd struct
			NULL,                                               // DXGI adapter 
			D3D_DRIVER_TYPE_HARDWARE,                           // Driver type
			NULL,                                               // Software
			NULL,                                               // Flags 
			NULL,                                               // Feature levels 
			NULL,                                               // Feature levels
			D3D11_SDK_VERSION,                                  // DirectX SDK version
			&scd,                                               // Swapchain description struct
			&swapchain,                                         // Pointer to pointer to swapchain
			&dev,                                               // Pointer to pointer to device
			NULL,                                               // Feature level
			&devcon                                             // Device context
		);

		// Create the back buffer render target
		ID3D11Texture2D* pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		devcon->OMSetRenderTargets(1, &backbuffer, NULL);

		// Create and assign viewport
		viewport.Width = SCREEN_WIDTH;
		viewport.Height = SCREEN_HEIGHT;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = D3D11_MIN_DEPTH;
		viewport.MaxDepth = D3D11_MAX_DEPTH;

		devcon->RSSetViewports(1, &viewport);
	};

	/// <summary>
	/// Default destructor, releases the memory used by DirectX.
	/// </summary>
	~RenderingEngine() {
		swapchain->SetFullscreenState(FALSE, NULL);
		swapchain->Release();
		dev->Release();
		devcon->Release();
		backbuffer->Release();
	};

	/// <summary>
	/// Render a frame to the render target.
	/// </summary>
	void RenderFrame(std::vector<GameObject> gameObjects) {
		for (int i = 0; i < gameObjects.size(); i++) {
			GameObject gameObject = gameObjects.at(i);
			Component* component = gameObject.GetComponent<MeshRenderer>();
			MeshRenderer* meshRenderer;

			if (component != nullptr) {
				meshRenderer = (MeshRenderer*) component;
			}
			else {
				continue;
			}

			Transform* transform = (Transform*)gameObject.GetComponent<Transform>();

			ID3D11Buffer* vertexBuffer = meshRenderer->CreateVertexBuffer(dev, devcon);
			ID3D11Buffer* transformMatricesBuffer = meshRenderer->CreateTransformMatricesBuffer(*transform, camera, dev, devcon);

			meshRenderer->material->pShader->SetAsActiveShader(devcon);
			devcon->VSSetConstantBuffers(0, 1, &transformMatricesBuffer);

			UINT stride = meshRenderer->material->GetSizeOfElementsArray();
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			devcon->Draw(meshRenderer->mesh->numberOfVertices, 0);

			// Render the back buffer to the screen
			swapchain->Present(0, 0);
		}
	}
};