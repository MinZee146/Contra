#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "Game.h"
#include "Textures.h"
#include <dinput.h>
#include "Sprite.h"
#include "Sprites.h"
#include "Maps.h"
#include "Animation.h"
#include "Animations.h"
#include "SampleKeyEventHandler.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "Stage1Map.h"


#define WINDOW_CLASS_NAME L"GameWindow"
#define MAIN_WINDOW_TITLE L"CONTRA"
#define WINDOW_ICON_PATH L"contra.ico"

#define WINDOW_WIDTH 290
#define WINDOW_HEIGHT 270

#define BACKGROUND_COLOR D3DXCOLOR(255.0f/255, 255.0f/255, 255.0f/255, 0.0f)

CSampleKeyHandler* keyHandler;
vector<LPGAMEOBJECT> objects;
CMap* Map = NULL;
LPBILL Bill = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//Them GameManager va ScreenManager de quan ly thay vi quan ly don le => Ham nay chi chua 2 instance cua GM va SM
void Update(DWORD dt)
{
	ScreenManager::GetInstance()->Update(Map, Bill, dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);


		//Dung Screen Manager de quan ly doan nay
		ScreenManager::GetInstance()->Render(Map, Bill);

		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	//Ti hoi CDUY xem cai nay de lam cai gi
	
	//RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };   
	//AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);  

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,    // width of the window
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}
	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {

	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, WINDOW_WIDTH, WINDOW_HEIGHT);

	LPGAME game = CGame::GetInstance();
	game->Init(hWnd, hInstance);
	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	//Dung GameManager de LoadStage len tai day
	
	Map = new Stage1Map(0, 240, WORLD1_WIDTH, WORLD1_HEIGHT);
	Bill = new CBill(100.0f, 100.0f);
	Map->LoadResource();
	Bill->LoadResource();
	
	
	SetWindowPos(hWnd, 0, 0, 0, WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}