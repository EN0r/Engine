#pragma once
#include <iostream>
#include <bitset>
#include <array>
#include <memory>
#include <vector>
#include "settings.h"
#include "vec2d.h"

#ifdef linux
#define NULL 0
#endif

class RdEntity;
class Component;
class RdEntityManager;

namespace componentSystem
{
	
	size_t getUniqueComponentID()
	{
		static size_t lastID = 0u; // makes a unsigned int of 0
		return lastID++;
	}

	template<typename T>
	size_t getComponentID()
	{
		static_assert(std::is_base_of<Component, T>::value, "Assert check on l19!"); // checks if The template class is derived of component.
		static const size_t tID = getUniqueComponentID();
		return tID;
	}
}

class RdEntity
{
private:
	std::array<Component*, settings::m_Ent> componentList;
	std::vector<std::unique_ptr<Component>> components;
	std::bitset<settings::m_Ent> bitsets;
public:
	std::string name = "NULL";
	void start(SDL_Renderer* renderer); // { for (auto& comp : componentList) comp->start(); }
	void update(SDL_Renderer* renderer);
	void init(SDL_Renderer* renderer);
	template<typename T>
	bool hasComponent() const
	{
		return bitsets[componentSystem::getComponentID<T>()];
	}

	template<typename T, typename... args>
	T& addComponent(args&&... argV)
	{
		T* component(new T(std::forward<args>(argV)...));
		std::unique_ptr<Component> uqPointer(component);
		components.emplace_back(std::move(uqPointer));
		component->parentEntity = this; // Component is being set here but for some reason it's nullptr elsewhere.
		if (component->init())
		{
			componentList[componentSystem::getComponentID<T>()] = component;
			bitsets[componentSystem::getComponentID<T>()] = true;
			return *component;
		}
		return *static_cast<T*>(NULL);
	}
	
	// This is a hotfix. Should be changed in the future as it's going to cause problems down the line.
	float x, y;

	template<typename T>
	T& getComponent()
	{
		auto ptr(componentList[componentSystem::getComponentID<T>()]);
		return *static_cast<T*>(ptr);
	}
};


class Component
{
private:

public:
	RdEntity* parentEntity = new RdEntity;
	// every component will have these
	virtual bool init() { return true; }
	virtual void start(SDL_Renderer* renderer)
	{

	}
	virtual void update(SDL_Renderer* renderer)
	{

	}
};

void RdEntity::start(SDL_Renderer* renderer = nullptr)
{
	for (const auto& component : componentList)
		if(component != nullptr)
			component->start(renderer);
	//for (auto& comp : componentList) comp->start();
}

void RdEntity::update(SDL_Renderer* renderer = nullptr)
{
	for (auto& component : componentList) 
		if(component != nullptr)
			component->update(renderer);
}

 void RdEntity::init(SDL_Renderer* renderer)
{
	 for (auto& component : componentList)
		 if (component != nullptr) // Fixed but where it was checking fields in array which never exists.
			 component->init();
}

class RdEntityManager
{
private:
	static RdEntityManager* instance;
	RdEntityManager() {}
public:
	std::vector<std::unique_ptr<RdEntity>> oEntityList;

	static RdEntityManager* getInstance()
	{
		if (instance == NULL)
			instance = new RdEntityManager;
		return instance;
	}
	void start(SDL_Renderer* renderer = nullptr);
	void update(SDL_Renderer* renderer = nullptr);
	void init(SDL_Renderer* renderer = nullptr);
	void addEntity(RdEntity* ent);
	void releaseEntity(RdEntity* ent); // releases entity from memory

};
RdEntityManager* RdEntityManager::instance;

void RdEntityManager::init(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < oEntityList.size(); i++)
	{
		if (renderer != nullptr)
			oEntityList[i]->init(renderer);
	}
}

void RdEntityManager::start(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < oEntityList.size(); i++)
	{
		if(renderer != nullptr)
			oEntityList[i]->start(renderer);
	}
}

void RdEntityManager::update(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < oEntityList.size(); i++)
	{
		if (renderer != nullptr)
			oEntityList[i]->update(renderer);
	}
}

void RdEntityManager::addEntity(RdEntity* ent)
{
	std::unique_ptr<RdEntity> entPointer(ent);
	oEntityList.emplace_back(std::move(entPointer));
}

void RdEntityManager::releaseEntity(RdEntity* ent)
{

}

