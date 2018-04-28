// ffmpegtest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ReadThread.h"


int main(int argc, char* argv[])
{
	av_register_all();

	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		return -1;
	}

	SDL_Window *screen = SDL_CreateWindow("Hello", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		300,300,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!screen) {
		return -1;
	}

	ReadThread readThread;
	readThread.start();
	while (true)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		default:
			break;
		}
	}

	return 0;
}

