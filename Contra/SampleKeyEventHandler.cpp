#include "SampleKeyEventHandler.h"
#include "Game.h"
#include "Bill.h"
using namespace std;
extern CBill* bill;

void CSampleKeyHandler::OnKeyDown(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_UPARROW:
		bill->SetState(BILL_STATE_JUMP); break;
	}
}
void CSampleKeyHandler::OnKeyUp(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_UPARROW:
		bill->SetState(BILL_STATE_RELEASE_JUMP); break;
	case DIK_DOWNARROW:
		bill->SetState(BILL_STATE_LIE_RELEASE); break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states) {
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHTARROW)) {
		bill->SetState(BILL_STATE_RUNNING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFTARROW)) {
		bill->SetState(BILL_STATE_RUNNING_LEFT);
	}
	else {
		bill->SetState(BILL_STATE_IDLE);
	}
	if (game->IsKeyDown(DIK_DOWNARROW)) {
		bill->SetState(BILL_STATE_LIE);
	}
}