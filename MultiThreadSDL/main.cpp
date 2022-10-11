#include "player.h"
#include "Bomb.h"
#include "Zombie.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>


SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

int main(int argc, char* argv[])
{
	// --------------------------------------------------- Initiallaizing and loading variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	const Uint8* keyState; 
	SDL_Rect cameraRect = { 0, 0, 640, 480 };
	int levelWidth, levelHeight;
	bool bomb = false;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, "player1.png", 20, 20, 3, 4);
	Player player2(renderTarget, "player2.png", 600, 400, 3, 4);

	Bomb b(renderTarget, "bomb2.png", -200, 200, 3, 4);
	Bomb b2(renderTarget, "bomb2.png", -200, 200, 3, 4);

	Zombie zombie;
	Zombie zombies[6];

	for (int i = 0; i < 5; i++)
	{
		zombies[i] = zombie;
		zombies[i].SetTexture(renderTarget, "zombie2.png");
	}

	SDL_Texture* texture = LoadTexture("rect2.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
	
	bool isRunning = true;
	SDL_Event ev;

	int i = 0;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;
		while (SDL_PollEvent(&ev) != 0)
		{
			// --------------------------------------------------- Getting the quit and keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
				case SDLK_SPACE:
					b.toggleBomb(player1.GetOriginX(), player1.GetOriginY());
					break;
				case SDLK_m:
					b2.toggleBomb(player2.GetOriginX(), player2.GetOriginY());
					break;
				default:
					break;
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		
		player1.Update(delta, keyState, zombie);
		player2.Update(delta, keyState, zombie);		// not testing colision with ´zombies but the default zombie

		b.Update(delta);
		b2.Update(delta);

		//zombie.Update(delta, player1.GetOriginX(), player1.GetOriginY(), player2.GetOriginX(), player2.GetOriginY(), b, b2);

		for (int i = 0; i < 5; i++)
		{
			zombies[i].Update(delta, player1.GetOriginX(), player1.GetOriginY(), player2.GetOriginX(), player2.GetOriginY(), b, b2);
		}

		/*
		
		cameraRect.x = player1.GetOriginX() - 320;
		cameraRect.y = player1.GetOriginY() - 240;

		if (cameraRect.x < 0)
			cameraRect.x = 0;
		if (cameraRect.y < 0)
			cameraRect.y = 0;

		if (cameraRect.x + cameraRect.w >= levelWidth)
			cameraRect.x = levelWidth - 640;
		if (cameraRect.y + cameraRect.h >= levelHeight)
			cameraRect.y = levelHeight - 480;
		
		*/
		
		// --------------------------------------------------- Drawing the cuurent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &cameraRect, NULL);

		player1.Draw(renderTarget);
		player2.Draw(renderTarget);

		b.Draw(renderTarget);
		b2.Draw(renderTarget);

		//zombie.Draw(renderTarget);

		for (int i = 0; i < 5; i++)
		{
			zombies[i].Draw(renderTarget);
		}
		
		SDL_RenderPresent(renderTarget);
	}

	// --------------------------------------------------- Freeing the memory
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);
	window = nullptr;
	renderTarget = nullptr;
	texture = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;

}

//^^^^°°abortb#i*
