#include "Stage1Map.h"

void CMap::LoadResource()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(10, TEXTURE_PATH_MAP1);
	CSprites* sprites = CSprites::GetInstance();
	LPTEXTURE texMap = textures->Get(10);
	sprites->Add(10050, 0, 0, 3328, 240, texMap);
}