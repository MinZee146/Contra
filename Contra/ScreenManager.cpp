#include "ScreenManager.h"

using namespace std;

ScreenManager* ScreenManager::__instance = NULL;

void Render(CMap* Map1, LPBILL Bill)
{
	Map1->Render();
	Bill->Render();
}

void Update(CMap* Map1, LPBILL Bill, DWORD dt)
{
	Map1->Update(dt, Bill);
	Bill->Update(dt);

	//camera theo nv
	float cx, cy;
	Bill->GetPosition(cx, cy);
	cx -= 290 / 2;
	cy = 0;
	if (cx < 0)
		cx = 0;
	CGame::GetInstance()->SetCamPos(cx, cy);
}