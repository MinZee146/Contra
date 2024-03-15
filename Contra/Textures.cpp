#include <Windows.h>
#include "Game.h"
#include "Textures.h"

CTextures* CTextures::__instance = NULL;

CTextures::CTextures() {

}

CTextures* CTextures::GetInstance() {
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath) {
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE CTextures::Get(unsigned int i) {
	return textures[i];
}