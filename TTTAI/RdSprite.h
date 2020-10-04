#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>
#include "componentSystem.h"
#include "RdTransform.h"

class RdSprite : Component
{
private: 
	float w, h;
	SDL_Texture* tex = NULL;
	SDL_Surface* surf = NULL;
	bool loadSurface(std::string directory);
	void drawBitMap(SDL_Renderer* renderer);
	SDL_Rect tBox = { 0,0,0,0 };
	RdTransform* transform = &parentEntity->getComponent<RdTransform>();
public:
	SDL_Texture* getTexture() { return tex; } // only need a getter as it's private.
	bool visible = true;
	std::string dir; // ./assets/Man/Man.png

	~RdSprite();
	RdSprite(std::string directory);
	bool init() override final;
	void update(SDL_Renderer* renderer) override final;
	void start(SDL_Renderer* renderer) override final;

};

bool RdSprite::init()
{

	return true;
}


RdSprite::RdSprite(std::string directory)
{
	dir = directory;
}

RdSprite::~RdSprite()
{
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
}

bool RdSprite::loadSurface(std::string directory)
{
	surf = IMG_Load(directory.c_str());
	if (surf) // assuming this returns bool
		return true;
	return false;
}

void RdSprite::drawBitMap(SDL_Renderer* renderer)
{
	SDL_CreateTextureFromSurface(renderer,surf);
	SDL_FreeSurface(surf); // here to prevent memory leak e.g if they load surf and draw w/o this then it will have big memory leak.
}

void RdSprite::update(SDL_Renderer* renderer) 
{
	// load the texture once
	if (this->loadSurface(dir))
	{

	}

	std::cout << "???" << std::endl;
}
void RdSprite::start(SDL_Renderer* renderer) 
{

}