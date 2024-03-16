#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Textures.h"
#include "Bill.h"
#include "Sprite.h"

#define WORLD_WIDTH 3328
#define WORLD_HEIGHT 240
class CMap {
	LPSPRITE map;
	static CMap* __instance;
	float x;
	float y;
	float width;
	float height;

public:
	static CMap* GetInstace();
	CMap(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	void setMap(LPSPRITE);
	float ConvertX(float x);
	float ConvertY(float y);
	float ConvertWorldX(float x);
	float ConvertWorldY(float y);
	float getx() { return x; }
	float gety() { return y; }
	void Update(DWORD, CBill*);
	void Render();
};