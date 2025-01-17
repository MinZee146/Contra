#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>


using namespace std;

class CGameObject
{
protected:
	float x;
	float y;
	float vx;
	float vy;
	int nx;
	int state;
public:
	CGameObject();
	CGameObject(float x, float y) :CGameObject(){ this->x = x; this->y = y; }

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }
	float GetSpeedVx() { return vx; }
	float GetSpeedVy() { return vy; }
	float GetX() { return x; }
	float GetY() { return y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;

