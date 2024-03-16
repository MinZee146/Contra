#include "SampleKeyEventHandler.h"
#include "Game.h"
#include "Bill.h"
using namespace std;
extern CBill* bill;

void CSampleKeyHandler::OnKeyDown(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_K:
		bill->SetState(BILL_STATE_JUMP); break;
	}
}
void CSampleKeyHandler::OnKeyUp(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_K:
		bill->SetState(BILL_STATE_RELEASE_JUMP); break;
	case DIK_S:
		bill->SetState(BILL_STATE_LIE_RELEASE); break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states) {
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_D)) {
		bill->SetState(BILL_STATE_RUNNING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_A)) {
		bill->SetState(BILL_STATE_RUNNING_LEFT);
	}
	else {
		bill->SetState(BILL_STATE_IDLE);
	}
	if (game->IsKeyDown(DIK_S)) {
		bill->SetState(BILL_STATE_LIE);
	}
}