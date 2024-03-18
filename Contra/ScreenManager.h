#pragma once
#include <Windows.h>
#include <d3dx10.h>
#include "Maps.h"
#include "GameObject.h"
#include "Bill.h"

class ScreenManager
{
private:
	static ScreenManager* __instance;
	LPBILL Bill;
public:
	static ScreenManager* GetInstance()
	{
		if (__instance == NULL)
		{
			__instance = new ScreenManager();
		}
		return __instance;
	}
	ScreenManager() {};
	void Render(CMap* Map1, LPBILL Bill) {};
	void Update(CMap* Map1, LPBILL Bill, DWORD dt) {};
};