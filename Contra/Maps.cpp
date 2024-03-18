#include "Maps.h"

using namespace std;
CMap* CMap::__instance = NULL;
void CMap::Update(DWORD dt, CBill* bill) {
	if (bill->GetX() >= width / 2 && bill->GetX() <= width - SCREEN_WIDTH / 2)
		this->x += bill->GetSpeedVx() * dt;
	float right_edge = width - SCREEN_WIDTH;
	if (this->x <= 0 || this->x >= right_edge)
	{
		if (this->x <= 0)
			this->x = 0;
		else
			this->x = right_edge;
	}
	this->Render();
}
float CMap::ConvertX(float x)
{
	return width / 2 - x;
}
float CMap::ConvertY(float y)
{

	return y - height / 2;
}
float CMap::ConvertWorldX(float x)
{
	return x - this->x;
}
float CMap::ConvertWorldY(float y)
{
	return this->y - y;
}

void CMap::Render() {
	float Cx = ConvertX(x);
	float Cy = ConvertY(y);
	this->map->Draw(Cx, Cy);
}

void CMap::setMap(LPSPRITE map) {
	this->map = map;
}
