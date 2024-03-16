/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 05 - SCENE MANAGER

	This sample illustrates how to:

		1/ Read scene (textures, sprites, animations and objects) from files
		2/ Handle multiple scenes in game

	Key classes/functions:
		CScene
		CPlayScene


HOW TO INSTALL Microsoft.DXSDK.D3DX
===================================
1) Tools > NuGet package manager > Package Manager Console
2) execute command :  Install-Package Microsoft.DXSDK.D3DX


================================================================ */
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
#include "Map.h"
#include "Animation.h"
#include "Animations.h"

#include "SampleKeyEventHandler.h"

#include "Bill.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"CONTRA"
#define WINDOW_ICON_PATH L"contra.ico"

#define TEXTURES_DIR L"Texture"
#define TEXTURE_PATH_BILL TEXTURES_DIR "\\contra2-transparent.png"
#define TEXTURE_PATH_MAP1 TEXTURES_DIR "\\__ContraMapStage1BG.png"

#define BACKGROUND_COLOR D3DXCOLOR(255.0f/255, 255.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

CBill* bill = NULL;
CMap* map = NULL;
#define BILL_START_X 100.0f
#define BILL_START_Y 100.0f
CSampleKeyHandler* keyHandler;
vector<LPGAMEOBJECT> objects;

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

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/


void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(0, TEXTURE_PATH_BILL);
	textures->Add(10, TEXTURE_PATH_MAP1);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));


	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE texBill = textures->Get(0);
	LPTEXTURE texMap = textures->Get(10);

	// readline => id, left, top, right, bottom 
	//RUN RIGHT
	sprites->Add(10001, 25, 24, 44, 59, texBill);
	sprites->Add(10002, 90, 27, 110, 58, texBill);
	sprites->Add(10003, 157, 25, 173, 59, texBill);
	//RUN LEFT
	sprites->Add(10011, 1433, 26, 1458, 59, texBill);
	sprites->Add(10012, 1368, 27, 1393, 58, texBill);
	sprites->Add(10013, 1303, 26, 1326, 59, texBill);
	//LIE RIGHT
	sprites->Add(10014, 927, 42, 927 + 32, 42 + 16, texBill);
	//LIE LEFT
	sprites->Add(10015, 1044, 43, 1044 + 32, 43 + 16, texBill);
	//JUMP RIGHT
	sprites->Add(10016, 805, 98, 805 + 16, 98 + 20, texBill);
	sprites->Add(10017, 868, 99, 868 + 19, 99 + 16, texBill);
	sprites->Add(10018, 935, 96, 935 + 16, 96 + 20, texBill);
	sprites->Add(10019, 999, 99, 999 + 19, 99 + 16, texBill);
	//JUMP LEFT
	sprites->Add(10020, 1247, 98, 1247 + 16, 98 + 20, texBill);
	sprites->Add(10021, 1181, 99, 1181 + 19, 99 + 16, texBill);
	sprites->Add(10022, 1117, 96, 1117 + 16, 96 + 20, texBill);
	sprites->Add(10023, 1050, 99, 1050 + 19, 99 + 16, texBill);
	//INDLE RIGHT
	sprites->Add(10024, 742, 26, 742 + 23, 26 + 33, texBill);
	//INDLE LEFT
	sprites->Add(10025, 1303, 26, 1303 + 23, 26 + 33, texBill);

	sprites->Add(10050, 0, 0, 3328, 240, texMap);
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(ID_ANI_RUNNING_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(ID_ANI_RUNNING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10014);
	animations->Add(ID_ANI_LYING_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10015);
	animations->Add(ID_ANI_LYING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10016);
	ani->Add(10017);
	ani->Add(10018);
	ani->Add(10019);
	animations->Add(ID_ANI_JUMPING_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10020);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(ID_ANI_JUMPING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10024);
	animations->Add(ID_ANI_BILL_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10025);
	animations->Add(ID_ANI_BILL_IDLE_LEFT, ani);

	bill = new CBill(BILL_START_X, BILL_START_Y);
	map = new CMap(0, 240, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->setMap(sprites->Get(10050));
}
void Update(DWORD dt)
{
	//CGame::GetInstance()->GetCurrentScene()->Update(dt);
	// Demo
	bill->Update(dt);
	map->Update(dt, bill);
}

/*
	Render a frame
*/
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

		map->Render();
		bill->Render();

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


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

	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,    // width of the window
			wr.bottom - wr.top,
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
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);
	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}