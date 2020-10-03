/*
#pragma once
#include "componentSystem.h"
#include "RdTransform.h"
#include "SDL.h"
class boxCollider2D : public Component
{
private:
	RdTransform* transform = nullptr;
	bool AABB(RdTransform bTransform);
	float w, h;
	SDL_Rect tBox = {0,0,0,0};
	RdEntityManager* entityManager = RdEntityManager::getInstance();
	bool colliding = false;
public:
	boxCollider2D(float w, float h);
	bool drawOutline = true;
	bool init() override final 
	{ 
		transform = &parentEntity->getComponent<RdTransform>(); 
		return true; 
	}
	void update(SDL_Renderer* renderer) override final
	{
		//tBox.x = transform->position.x;
		//tBox.y = transform->position.y;
		if (drawOutline)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(renderer, &tBox);
		}
		if (entityManager->oEntityList.size() > NULL)
		{
			for (size_t i = 0; i < entityManager->oEntityList.size(); i++)
			{
				if (entityManager->oEntityList[i]->hasComponent<boxCollider2D>())
				{
					if (AABB(entityManager->oEntityList[i]->getComponent<RdTransform>()))
					{
						colliding = true;
					}
				}

			}
		}
	}
	void start(SDL_Renderer* renderer) override final {}
};

boxCollider2D::boxCollider2D(float w1, float h1)
{
	tBox.w = w;
	tBox.h = h;
	this->w = w1;
	this->h = h1;
}

bool boxCollider2D::AABB(RdTransform bTransform)
{
	if (this->transform->position.x + w >= bTransform.position.x &&
	bTransform.position.x + bTransform.scale.y >= this->transform->position.x &&
	this->transform->position.y + h >= bTransform.position.y &&
	bTransform.position.y + bTransform.scale.y >= this->transform->position.y)
	{
		return true;
	}
	return false;
}
*/