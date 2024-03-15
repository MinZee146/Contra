#pragma once
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <Windows.h>
#include <d3d10.h>
#include <D3DX10.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Texture.h"

#include "KeyEventHandler.h"

#define MAX_FRAME_RATE 60

#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state
	ID3DX10Sprite* spriteObject = NULL;				// Sprite handling object

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
	HINSTANCE hInstance;
	 

public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	void InitKeyboard(LPKEYEVENTHANDLER handler);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	static CGame* GetInstance();

	~CGame();
};