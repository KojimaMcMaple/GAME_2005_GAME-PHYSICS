// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "Globals.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char * args[])
{
	Uint32 frameStart, frameTime;
	UINT32 frames = 0;


	// show console
	AllocConsole();
	freopen("CON", "w", stdout);


	TheGame::Instance()->init("GAME2005_A3_LeTrung_ShuDeng", 100, 100, Globals::kWindowWidth, Globals::kWindowHeight, false);

	while (TheGame::Instance()->isRunning())
	{
		frameStart = SDL_GetTicks();

		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime< DELAY_TIME)
		{
			SDL_Delay(int(DELAY_TIME - frameTime));
		}

		frames++;
		TheGame::Instance()->setFrames(frames);

	}

	TheGame::Instance()->clean();
	return 0;
}

