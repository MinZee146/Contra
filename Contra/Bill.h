#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "BillStats.h"

class CBill : public CGameObject
{
protected:
	BOOLEAN isLying;
	float vx;
public:
	CBill(float x, float y) :CGameObject(x, y) 
	{
		isLying = false;
		vx = 0.0f;
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void LoadResource() override {};
};
typedef CBill* LPBILL;


