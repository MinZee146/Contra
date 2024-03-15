#include "GameObject.h"
#include "Game.h"
#include <d3dx10.h>
CGameObject::CGameObject()
{
	this->x = x;
	this->y = y;
	vx = vy = 0;
	nx = 1;
	state = -1;
}