#pragma once
#include <SDL.h>
#include <string>
#include <windows.h>
#include "componentSystem.h"
class rdBitMap : Component
{
private: 
	std::string dir;
	SDL_Texture* tex = NULL;
	SDL_Surface* surf = NULL;
	bool loadSurface(std::string directory);
	SDL_Texture* getTexture() { return tex; } // only need a getter as it's private.
	rdBitMap(std::string directory);
	void drawBitMap(SDL_Renderer* renderer);
public:
	bool visible = true;

	bool init() override final {}
	void update() override final {}
	void start() override final {}

};

rdBitMap::rdBitMap(std::string directory)
{
	dir = directory;
}

rdBitMap::~rdBitMap()
{
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
}

bool rdBitMap::loadSurface(std::string directory)
{
	if (SDL_LoadBMP(directory.c_str())) // assuming this returns bool
		return true;
	return false;
}

void rdBitMap::drawBitMap(SDL_Renderer* renderer)
{
	SDL_CreateTextureFromSurface(renderer,surf);
	SDL_FreeSurface(surf); // here to prevent memory leak e.g if they load surf and draw w/o this then it will have big memory leak.
}

