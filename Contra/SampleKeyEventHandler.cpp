#include "SampleKeyEventHandler.h"
#include "Game.h"
#include "Bill.h"
using namespace std;
extern LPBILL Bill;

void CSampleKeyHandler::OnKeyDown(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_K:
		Bill->SetState(BILL_STATE_JUMP); break;
	}
}
void CSampleKeyHandler::OnKeyUp(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_K:
		Bill->SetState(BILL_STATE_RELEASE_JUMP); break;
	case DIK_S:
		Bill->SetState(BILL_STATE_LIE_RELEASE); break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states) {
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_D)) {
		Bill->SetState(BILL_STATE_RUNNING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_A)) {
		Bill->SetState(BILL_STATE_RUNNING_LEFT);
	}
	else {
		Bill->SetState(BILL_STATE_IDLE);
	}
	if (game->IsKeyDown(DIK_S)) {
		Bill->SetState(BILL_STATE_LIE);
	}
}