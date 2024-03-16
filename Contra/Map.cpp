#include "Map.h"

using namespace std;
CMap* CMap::__instance = NULL;
void CMap::Update(DWORD dt, CBill* bill) {
	if (bill->GetX() >= width / 2 && bill->GetX() <= WORLD_WIDTH - width / 2)
		this->x += bill->GetSpeedVx() * dt;
	float right_edge = WORLD_WIDTH - width;
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
	return WORLD_WIDTH / 2 - x;
}
float CMap::ConvertY(float y)
{

	return y - WORLD_HEIGHT / 2;
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