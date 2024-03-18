#pragma once
#include "Maps.h"

#define WORLD1_WIDTH 3328
#define WORLD1_HEIGHT 240

#define BILL_START_X 100.0f
#define BILL_START_Y 100.0f

class Stage1Map : public CMap
{
public:
	Stage1Map(float x, float y, float width, float height) :CMap(x, y, width, height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	void LoadResource() override {};
};