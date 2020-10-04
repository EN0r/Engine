#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "settings.h"
#include "gameMain.h"
#include "componentSystem.h"
#include "RdTransform.h"
#include "BoxCollider2D.h"
#include "RdSprite.h"
#include "glad/glad.h"
#include "vendor/imgui/examples/imgui_impl_sdl.h"
#include "vendor/imgui/examples/imgui_impl_opengl3.h"

int main(int argc, char* argv[])
{
	gameL L;
	SDL_Renderer* renderer;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings::windowWidth, settings::windowHeight, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);
	IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG);
	if (settings::devConsole == true)
	{
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window,glContext);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		std::cout << "ERROR: Cannot load Glad GL" << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontFromFileTTF("./fonts/Verdana.ttf", 18.0f, NULL, NULL);
	ImGui::StyleColorsDark();

	const char* glsl_version = "#version 130";
	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init(glsl_version);
	


	RdEntityManager::getInstance()->init();
	RdEntityManager::getInstance()->start(renderer);
	L.start(renderer,window);
	bool shown = false;
	
	while (1)
	{
		SDL_Event msg;
		SDL_PollEvent(&msg);

		switch (msg.type)
		{
			// maybe add some frametime here
		ImGui_ImplSDL2_ProcessEvent(&msg);
		case SDL_QUIT:
			SDL_Quit();
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			return 1;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		L.rendermain(renderer);
		L.uiUpdate(window);

		SDL_RenderPresent(renderer);
		SDL_GL_SwapWindow(window);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	SDL_Quit();
	return -1;
}