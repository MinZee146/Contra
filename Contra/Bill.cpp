#include "Bill.h"
#include "Game.h"


void CBill::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
	vy += BILL_GRAVITY*dt;
	vx = BILL_RUN_SPEED;
	if (y > GROUND_Y) {
		vy = 0;
		y = GROUND_Y;
	}
	if (nx < 0) {
		vx = -BILL_RUN_SPEED;
	}
	if (vx > 0 && x >3150) x = 3150;
	if (vx < 0 && x < 0) x = 0;
}
void CBill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (y < GROUND_Y) {
		if (nx >= 0) {
			aniId = ID_ANI_JUMPING_RIGHT;
		}
		else {
			aniId = ID_ANI_JUMPING_LEFT;
		}
	}
	else
	if (isLying) {
		if (nx > 0) {
			aniId = ID_ANI_LYING_RIGHT;
		}
		else {
			aniId = ID_ANI_LYING_LEFT;
		}
	}
	else
	if (vx == 0) {
		if (nx > 0) {
			aniId = ID_ANI_BILL_IDLE_RIGHT;
		}
		else {
			aniId = ID_ANI_BILL_IDLE_LEFT;
		}
	}
	else if(vx > 0) {
		aniId = ID_ANI_RUNNING_RIGHT;
	}
	else {
		aniId = ID_ANI_RUNNING_LEFT;
	}
	if (aniId == -1) {
		aniId = ID_ANI_BILL_IDLE_RIGHT;
	}
	float d = 0;
	if (isLying) d = BILL_LIE_HEIGHT_ADJUST;

	animations->Get(aniId)->Render(x, y + d);
}

void CBill::SetState(int state) {
	switch (state)
	{
	case BILL_STATE_RUNNING_RIGHT:
		if (isLying) break;
		vx = BILL_RUN_SPEED;
		nx = 1;
		break;
	case BILL_STATE_RUNNING_LEFT:
		if (isLying) break;
		vx = -BILL_RUN_SPEED;
		nx = -1;
		break;
	case BILL_STATE_JUMP:
		if (isLying) break;
		if (y == GROUND_Y) {
			vy = -BILL_JUMP_SPEED;
		}
		break;
	/*case BILL_STATE_RELEASE_JUMP:
		if (vy < 0) vy += BILL_JUMP_SPEED / 2;
		break;*/
	case BILL_STATE_LIE:
		if (y == GROUND_Y) {
			state = BILL_STATE_IDLE;
			isLying = true;
			vx = 0; vy = 0;
		}
		break;
	case BILL_STATE_LIE_RELEASE:
		isLying = false;
		state = BILL_STATE_IDLE;
		break;
	case BILL_STATE_IDLE:
		vx = 0.0f;
		break;
	}
	CGameObject::SetState(state);
}