#ifndef FRAMEWORK_H
#include "framework.h"
#endif


class RENDERINGENGINE {
public:
	HWND hWnd;                                // Window handle
	ID3D11Device* dev;                        // DirectX device
	ID3D11DeviceContext* devcon;              // DirectX device context
	IDXGISwapChain* swapchain;                // DXGI swapchain
	ID3D11RenderTargetView* backbuffer;       // The backbuffer render target
	D3D11_VIEWPORT viewport;                  // The viewport


	RENDERINGENGINE();                        // Constructor
	~RENDERINGENGINE();                       // Destructor
	void RenderFrame();                       // Render a frame
};