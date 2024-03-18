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

void LoadResource() 
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(0, TEXTURE_PATH_BILL);

	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE texBill = textures->Get(0);
	// readline => id, left, top, right, bottom 
	//RUN RIGHT
	sprites->Add(10001, 25, 24, 44, 59, texBill);
	sprites->Add(10002, 90, 27, 110, 58, texBill);
	sprites->Add(10003, 157, 25, 173, 59, texBill);
	//RUN LEFT
	sprites->Add(10004, 1433, 26, 1458, 59, texBill);
	sprites->Add(10005, 1368, 27, 1393, 58, texBill);
	sprites->Add(10006, 1303, 26, 1326, 59, texBill);
	//LIE RIGHT
	sprites->Add(10007, 927, 42, 927 + 32, 42 + 16, texBill);
	//LIE LEFT
	sprites->Add(10008, 1044, 43, 1044 + 32, 43 + 16, texBill);
	//JUMP RIGHT
	sprites->Add(10009, 805, 98, 805 + 16, 98 + 20, texBill);
	sprites->Add(10010, 868, 99, 868 + 19, 99 + 16, texBill);
	sprites->Add(10011, 935, 96, 935 + 16, 96 + 20, texBill);
	sprites->Add(10012, 999, 99, 999 + 19, 99 + 16, texBill);
	//JUMP LEFT
	sprites->Add(10013, 1247, 98, 1247 + 16, 98 + 20, texBill);
	sprites->Add(10014, 1181, 99, 1181 + 19, 99 + 16, texBill);
	sprites->Add(10015, 1117, 96, 1117 + 16, 96 + 20, texBill);
	sprites->Add(10016, 1050, 99, 1050 + 19, 99 + 16, texBill);
	//IDLE RIGHT
	sprites->Add(10017, 742, 26, 742 + 23, 26 + 33, texBill);
	//IDLE LEFT
	sprites->Add(10018, 1303, 26, 1303 + 23, 26 + 33, texBill);

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
}