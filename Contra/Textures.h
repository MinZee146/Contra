#pragma once
#include <unordered_map>
#include <d3dx10.h>
#include "Texture.h"
using namespace std;

class CTextures {
private:
	static CTextures* __instance;
	unordered_map<int, LPTEXTURE> textures;
public:
	CTextures();
	void Add(int id, LPCWSTR filePath);
	LPTEXTURE Get(unsigned int i);
	static CTextures* GetInstance();
};
