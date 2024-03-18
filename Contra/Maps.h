#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Textures.h"
#include "Bill.h"
#include "Sprite.h"


#define TEXTURE_PATH_BILL TEXTURES_DIR "\\contra2-transparent.png"
#define TEXTURE_PATH_MAP1 TEXTURES_DIR "\\__ContraMapStage1BG.png"
#define SCREEN_WIDTH 290
#define SCREEN_HEIGHT 270

class CMap {
protected:
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
	virtual void LoadResource() = 0;
};