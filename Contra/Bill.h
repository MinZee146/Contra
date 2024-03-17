#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BILL_WIDTH 14

#define BILL_RUN_SPEED 1.0f
#define BILL_JUMP_SPEED 0.5f

#define BILL_GRAVITY 0.0025f

#define BILL_STATE_IDLE 0
#define BILL_STATE_RUNNING_RIGHT 100
#define BILL_STATE_RUNNING_LEFT 200

#define BILL_STATE_JUMP			300
#define BILL_STATE_RELEASE_JUMP    301

#define BILL_STATE_LIE				400
#define BILL_STATE_LIE_RELEASE		401

#define ID_ANI_BILL_IDLE_RIGHT 500
#define ID_ANI_BILL_IDLE_LEFT 501

#define ID_ANI_RUNNING_RIGHT 600
#define ID_ANI_RUNNING_LEFT 601

#define ID_ANI_JUMPING_RIGHT 700
#define ID_ANI_JUMPING_LEFT 701

#define ID_ANI_LYING_RIGHT 800
#define ID_ANI_LYING_LEFT 801

#define GROUND_Y 100.0f

#define BILL_LIE_HEIGHT_ADJUST 10.0f
class CBill : public CGameObject
{
protected:
	BOOLEAN isLying;
	float vx;
public:
	
	CBill(float x, float y) :CGameObject(x, y) {
		isLying = false;
		vx = 0.0f;
	}
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};


