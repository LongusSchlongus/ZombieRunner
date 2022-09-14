#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <iostream>
#include "player.h"
#include "Bomb.h"

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
	// Initiallaizing and loading variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	const Uint8* keyState; 
	SDL_Rect cameraRect = { 0, 0, 640, 480 };
	int levelWidth, levelHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, "player1.png", 0, 0, 3, 4);
	Player player2(renderTarget, "player2.png", 600, 400, 3, 4);

	Bomb bombObject(renderTarget, "bomb.png", -100, -100, 3, 4);
	Bomb bombArr[5] = { bombObject ,bombObject ,bombObject ,bombObject, bombObject };


	SDL_Texture* texture = LoadTexture("rect.png", renderTarget);
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
			// Getting the quit and keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
				case SDLK_SPACE:
					i++;
					std::cout << "bomb "<<i<<" droped!" << std::endl;
					bombArr[i].Spawn(player1.GetOriginX(), player1.GetOriginY());
					break;
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		for (int i = 0; i < 5; i++)
		{
			bombArr[i].Update(delta);
		}
		player1.Update(delta, keyState);
		player2.Update(delta, keyState);

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

		player1.intersectsWith(player2);

		// Drawing the cuurent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &cameraRect, NULL);

		player1.Draw(renderTarget);
		player2.Draw(renderTarget);

		for (int i = 0; i < 5; i++)
		{
			bombArr[i].Draw(renderTarget);
		}

		SDL_RenderPresent(renderTarget);
	}
	// Freeing the memory
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
