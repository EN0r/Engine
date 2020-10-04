
#pragma once
#include "componentSystem.h"
#include "RdTransform.h"
#include "SDL.h"
class boxCollider2D : public Component
{
private:
	RdTransform* transform = &parentEntity->getComponent<RdTransform>();
	bool AABB(RdTransform bTransform);
	float w, h;
	SDL_Rect tBox = {0,0,0,0};
	RdEntityManager* entityManager = RdEntityManager::getInstance();
	bool colliding = false;
public:
	boxCollider2D(float w = 0, float h = 0);
	bool drawOutline = true;
	bool init() override final 
	{ 
		if (parentEntity->hasComponent<RdTransform>())
		{
			// does not have any components
			std::cout << "CRITICAL ERROR: Transform was NOT FOUND in component: boxCollider2D" << std::endl;
			std::cout << "CONSTRUCTING NEW TRASNFORM." << std::endl;
			this->parentEntity->addComponent<RdTransform>().position.x = this->parentEntity->x;
			this->parentEntity->getComponent<RdTransform>().position.y = this->parentEntity->y;
			this->transform = &this->parentEntity->getComponent<RdTransform>();
		}
		if (this->transform == nullptr)
		{
			std::cout << "CRITICAL ERROR: Transform was NULL in component: boxCollider2D" << std::endl;
			std::cout << "CONSTRUCTING NEW TRASNFORM." << std::endl;
			this->parentEntity->addComponent<RdTransform>().position.x = this->parentEntity->x;
			this->parentEntity->getComponent<RdTransform>().position.y = this->parentEntity->y;
			this->transform = &this->parentEntity->getComponent<RdTransform>();
		}
		return true; 
	}
	void update(SDL_Renderer* renderer) override final
	{
		tBox.x = transform->position.x;
		tBox.y = transform->position.y;
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
	if (w1 == 0 && h1 == 0)
		std::cout << "WARNING: Not set size for boxCollider2D Component" << std::endl;

	this->w = w1;
	this->h = h1;
	tBox.w = w;
	tBox.h = h;
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