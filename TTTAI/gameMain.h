#pragma once
#include <SDL.h>
#include "componentSystem.h"
#include "RdTransform.h"
#include "BoxCollider2D.h"

class gameL
{

public:
	RdEntity* entity;
	void rendermain(SDL_Renderer* renderer);
	void start(SDL_Renderer* renderer);
};

void gameL::start(SDL_Renderer* renderer)
{
	/*entity = new RdEntity;
	RdEntityManager::getInstance()->addEntity(entity);
	entity->addComponent<RdTransform>();
	entity->getComponent<RdTransform>().position.x = 100;
	entity->addComponent<boxCollider2D>(100, 100);
	entity->x = 100;
	entity->y = 100;*/
}

void gameL::rendermain(SDL_Renderer* renderer)
{
	// this is game loop

	RdEntityManager::getInstance()->update(renderer);
	
}