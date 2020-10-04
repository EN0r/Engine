#pragma once
#include <SDL.h>
#include "componentSystem.h"
#include "RdTransform.h"
#include "BoxCollider2D.h"
#include "glad/glad.h"
#include <chrono>
#include <string>
#include "vendor/imgui/examples/imgui_impl_sdl.h"
#include "vendor/imgui/examples/imgui_impl_opengl3.h"

class gameL
{
private:
	ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	int countedFrame = 0;
	int framesSinceStart = 0;
	const int SCREEN_FPS = 60;
	int startTicks;
	int countedFrames = 0;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
public:
	RdEntity* entity;
	void rendermain(SDL_Renderer* renderer);
	void start(SDL_Renderer* renderer, SDL_Window* window); 
	void uiUpdate(SDL_Window* window);
};

void gameL::start(SDL_Renderer* renderer, SDL_Window* window)
{
	/*
	entity = new RdEntity;
	RdEntityManager::getInstance()->addEntity(entity);
	entity->addComponent<RdTransform>();
	entity->getComponent<RdTransform>().position.x = 100;
	entity->addComponent<boxCollider2D>(100, 100);
	entity->x = 100;
	entity->y = 100;
	*/
	startTicks = SDL_GetTicks();
	RdEntity* ent1 = new RdEntity;
	RdEntity* ent2 = new RdEntity;
	RdEntity* ent3 = new RdEntity;
	RdEntity* ent4 = new RdEntity;
	RdEntity* ent5 = new RdEntity;
	ent1->name = "ent1";
	ent2->name = "ent2";
	ent3->name = "ent3";
	ent4->name = "ent4";
	ent5->name = "ent5";
	RdEntityManager::getInstance()->addEntity(ent1);
	RdEntityManager::getInstance()->addEntity(ent2);
	RdEntityManager::getInstance()->addEntity(ent3);
	RdEntityManager::getInstance()->addEntity(ent4);
	RdEntityManager::getInstance()->addEntity(ent5);
}

void gameL::rendermain(SDL_Renderer* renderer)
{
	// this is game loop
	RdEntityManager::getInstance()->update(renderer);

}

void gameL::uiUpdate(SDL_Window* window)
{
	int fpsCapStartTicks = SDL_GetTicks();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();
	{
		ImGui::Begin("Scene editor");

		ImGui::TextColored(ImVec4(0.55, 0.55, 0.55, 1), "Entities");

		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < RdEntityManager::getInstance()->oEntityList.size(); n++)
		{
			ImGui::Text(std::string(std::to_string(n) + ":" +  RdEntityManager::getInstance()->oEntityList[n]->name).c_str());
		}
		ImGui::EndChild();

		//ImGui::EndChild();
		ImGui::End();
	}


	float avgFPS = countedFrames / ((SDL_GetTicks() - startTicks) / 1000.f);
	if (avgFPS > 2000000)
		avgFPS = 0;

	++countedFrames;

	// If frame finished early
	int frameTicks = SDL_GetTicks() - fpsCapStartTicks;
	if (frameTicks < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay((SCREEN_TICK_PER_FRAME - frameTicks) * 1.30);
	}




	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	ImGui::Render();
	glViewport(0, 0, settings::windowWidth, settings::windowHeight);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

